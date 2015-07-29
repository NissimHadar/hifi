//
//  LossList.cpp
//  libraries/networking/src/udt
//
//  Created by Clement on 7/27/15.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "LossList.h"

using namespace udt;
using namespace std;

void LossList::append(SequenceNumber seq) {
    assert(_lossList.back().second < seq);
    
    if (getLength() > 0 && _lossList.back().second + 1 == seq) {
        ++_lossList.back().second;
    } else {
        _lossList.push_back(make_pair(seq, seq));
    }
    _length += 1;
}

void LossList::append(SequenceNumber start, SequenceNumber end) {
    if (getLength() > 0 && _lossList.back().second + 1 == start) {
        _lossList.back().second = end;
    } else {
        _lossList.push_back(make_pair(start, end));
    }
    _length += seqlen(start, end);
}

void LossList::insert(SequenceNumber start, SequenceNumber end) {
    auto it = find_if_not(_lossList.begin(), _lossList.end(), [&start](pair<SequenceNumber, SequenceNumber> pair){
        return pair.second < start;
    });
    
    if (it == _lossList.end()) {
        // No overlap, simply insert
        _lossList.insert(it, make_pair(start, end));
        _length += seqlen(start, end);
    } else {
        // If it starts before segment, extend segment
        if (start < it->first) {
            _length += seqlen(start, it->first - 1);
            it->first = start;
        }
        
        if (end > it->second) {
            // If it goes further, find the actual end
            auto it2 = find_if(it, _lossList.end(), [&end](pair<SequenceNumber, SequenceNumber> pair){
                return end <= pair.second;
            });
            
            // If it ends inside a segment, change end (segment will be deleted)
            // Or backup iterator so segment doesn't get deleted
            if (it2->first <= end) {
                end = it2->second;
            } else {
                --it2;
            }
            
            // Change the end of the original segment
            _length += seqlen(it->second + 1, end);
            it->second = end;
            
            // remove all underlapping segments
            ++it; ++it2;
            while (it != it2) {
                _length -= seqlen(it->first, it->second);
                it = _lossList.erase(it);
            }
        }
    }
}

void LossList::remove(SequenceNumber seq) {
    auto it = find_if(_lossList.begin(), _lossList.end(), [&seq](pair<SequenceNumber, SequenceNumber> pair) {
        return pair.first <= seq && seq <= pair.second;
    });
    
    if (it != end(_lossList)) {
        if (it->first == it->second) {
            _lossList.erase(it);
        } else if (seq == it->first) {
            ++it->first;
        } else if (seq == it->second) {
            --it->second;
        } else {
            auto temp = it->second;
            it->second = seq - 1;
            _lossList.insert(it, make_pair(seq + 1, temp));
        }
        _length -= 1;
    }
}

void LossList::remove(SequenceNumber start, SequenceNumber end) {
    // Find the first segment sharing sequence numbers
    auto it = find_if(_lossList.begin(), _lossList.end(), [&start, &end](pair<SequenceNumber, SequenceNumber> pair) {
        return (pair.first <= start && start <= pair.second) || (start <= pair.first && pair.first <= end);
    });
    
    // If we found one
    if (it != _lossList.end()) {
        
        // While the end of the current segment is contained, either shorten it (first one only - sometimes)
        // or remove it altogether since it is fully contained it the range
        while (it != _lossList.end() && end >= it->second) {
            if (start <= it->first) {
                // Segment is contained, update new length and erase it.
                _length -= seqlen(it->first, it->second);
                it = _lossList.erase(it);
            } else {
                // Beginning of segment not contained, modify end of segment.
                // Will only occur sometimes one the first loop
                _length -= seqlen(start, it->second);
                it->second = start - 1;
                ++it;
            }
        }
        
        // There might be more to remove
        if (it != _lossList.end() && it->first <= end) {
            if (start <= it->first) {
                // Truncate beginning of segment
                _length -= seqlen(it->first, end);
                it->first = end + 1;
            } else {
                // Cut it in half if the range we are removing is contained within one segment
                _length -= seqlen(start, end);
                auto temp = it->second;
                it->second = start - 1;
                _lossList.insert(it, make_pair(end + 1, temp));
            }
        }
    }
}

SequenceNumber LossList::getFirstSequenceNumber() const {
    assert(getLength() > 0);
    return _lossList.front().first;
}

SequenceNumber LossList::popFirstSequenceNumber() {
    auto front = getFirstSequenceNumber();
    remove(front);
    return front;
}
