#pragma once

#include <QDir>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QFile>

struct Build {
    QString tag;
    int latestVersion;
    int buildNumber;
    QString installerZipURL;
};

struct LatestBuilds {
    bool getBuild(QString tag, Build* outBuild);

    QString defaultTag;
    std::vector<Build> builds;
    Build launcherBuild;
};

struct LoginResponse {
    QString accessToken;
    QString tokenType;
    QString refreshToken;
};

class LauncherState : public QObject {
    Q_OBJECT

    Q_PROPERTY(UIState uiState READ getUIState NOTIFY uiStateChanged);
    Q_PROPERTY(ApplicationState applicationState READ getApplicationState NOTIFY applicationStateChanged);
    Q_PROPERTY(float downloadProgress READ getDownloadProgress NOTIFY downloadProgressChanged);

public:
    LauncherState();
    ~LauncherState() = default;

    enum UIState {
        SPLASH_SCREEN = 0,
        LOGIN_SCREEN,
        DISPLAY_NAME_SCREEN,
        DOWNLOAD_SCREEN,
        DOWNLOAD_FINSISHED,
        ERROR_SCREEN,
        UI_STATE_NUM
    };

    enum class ApplicationState {
        Init,

        UnexpectedError,

        RequestingBuilds,
        GettingCurrentClientVersion,

        WaitingForLogin,
        RequestingLogin,

        DownloadingClient,
        DownloadingLauncher,
        DownloadingContentCache,

        InstallingClient,
        InstallingLauncher,
        InstallingContentCache,

        LaunchingHighFidelity
    };

    enum LastLoginError {
        NONE = 0,
        ORGINIZATION,
        CREDENTIALS,
        LAST_ERROR_NUM
    };

    Q_ENUM(UIState);
    Q_ENUM(ApplicationState)
    Q_ENUM(LastLoginError)

    Q_INVOKABLE QString getCurrentUISource() const;

    void ASSERT_STATE(LauncherState::ApplicationState state);
    void ASSERT_STATE(std::vector<LauncherState::ApplicationState> states);

    static void declareQML();

    UIState getUIState() const;

    void setLastLoginError(LastLoginError lastLoginError);
    LastLoginError getLastLoginError() const;

    void setApplicationStateError(QString errorMessage);
    void setApplicationState(ApplicationState state);
    ApplicationState getApplicationState() const;

    // Request builds
    void requestBuilds();
    Q_INVOKABLE void receivedBuildsReply();


    // Login
    Q_INVOKABLE void login(QString username, QString password);
    Q_INVOKABLE void receivedLoginReply();

    void requestSettings();
    Q_INVOKABLE void receivedSettingsReply();

    // Launcher
    void downloadLauncher();
    void installLauncher();

    // Client
    void downloadClient();
    void installClient();

    // Content Cache
    void downloadContentCache();
    void installContentCache();

    // Launching
    void launchClient();

    Q_INVOKABLE float getDownloadProgress() const { return _downloadProgress; }

signals:
    void updateSourceUrl(QString sourceUrl);
    void uiStateChanged();
    void applicationStateChanged();
    void downloadProgressChanged();

private slots:
    void clientDownloadComplete();
    void contentCacheDownloadComplete();
    void launcherDownloadComplete();

private:
    bool shouldDownloadContentCache() const;
    void getCurrentClientVersion();

    QString getContentCachePath() const;
    QString getClientDirectory() const;
    QString getClientExecutablePath() const;

    bool shouldDownloadLauncher();

    QNetworkAccessManager _networkAccessManager;
    LatestBuilds _latestBuilds;
    QDir _launcherDirectory;

    // Application State
    ApplicationState _applicationState { ApplicationState::Init };
    LoginResponse _loginResponse;
    LastLoginError _lastLoginError { NONE };
    QString _applicationErrorMessage;
    QString _currentClientVersion;
    QString _buildTag { QString::null };
    QString _contentCacheURL{ "https://orgs.highfidelity.com/content-cache/content_cache_small-only_data8.zip" }; // QString::null }; // If null, there is no content cache to download
    QString _loginTokenResponse;
    QString _homeLocation;
    QFile _clientZipFile;
    QFile _launcherZipFile;
    QFile _contentZipFile;

    float _downloadProgress { 0 };
};
