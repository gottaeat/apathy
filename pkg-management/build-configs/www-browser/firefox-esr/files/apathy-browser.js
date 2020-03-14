// local data storage
pref("browser.bookmarks.max_backups", 0);
pref("browser.cache.disk.enable", false);
pref("browser.cache.memory.enable", true);
pref("browser.cache.offline.enable", false);
pref("browser.formfill.enable", false);
pref("browser.library.activity-stream.enabled", false);
pref("browser.newtabpage.activity-stream.asrouter.userprefs.cfr.addons", false);
pref("browser.newtabpage.activity-stream.asrouter.userprefs.cfr.features", false);
pref("browser.newtabpage.activity-stream.feeds.section.highlights", false);
pref("browser.newtabpage.activity-stream.feeds.section.topstories", false);
pref("browser.newtabpage.activity-stream.feeds.snippets", false);
pref("browser.newtabpage.activity-stream.feeds.topsites", false);
pref("browser.newtabpage.activity-stream.showSearch", false);
pref("browser.newtabpage.enabled", false);
pref("browser.privatebrowsing.autostart", true);
pref("browser.sessionstore.privacy_level", 2);
pref("signon.autofillForms", false);

// search bar
pref("browser.search.suggest.enabled", false);
pref("browser.search.update", false);
pref("browser.urlbar.autoFill", false);
pref("browser.urlbar.maxRichResults", 0);
pref("browser.urlbar.speculativeConnect.enabled", false);
pref("browser.urlbar.suggest.bookmark", false);
pref("browser.urlbar.suggest.history", false);
pref("browser.urlbar.suggest.openpage", false);
pref("browser.urlbar.suggest.searches", false);

// network configuration
pref("browser.send_pings.require_same_host", true);
pref("captivedetect.canonicalURL", "");
pref("network.captive-portal-service.enabled", false);
pref("network.connectivity-service.enabled", false);
pref("network.cookie.cookieBehavior", 0);
pref("network.dns.disablePrefetch", true);
pref("network.http.referer.XOriginPolicy", 1);
pref("network.predictor.enabled", false);
pref("network.prefetch-next", false);
pref("network.security.esni.enabled", true);
pref("network.trr.bootstrapAddress", "9.9.9.9");
pref("network.trr.mode", 0);

// device fingerprinting
pref("beacon.enabled", false);
pref("browser.search.geoip.url", "");
pref("dom.battery.enabled", false);
pref("dom.gamepad.enabled", false);
pref("dom.push.enabled", false);
pref("dom.serviceWorkers.enabled", false);
pref("dom.vr.enabled", false);
pref("dom.webnotifications.enabled", false);
pref("general.useragent.override", "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
pref("geo.enabled", false);
pref("geo.wifi.uri", "");
pref("media.navigator.enabled", false);
pref("media.peerconnection.enabled", false);
pref("media.webspeech.synth.enabled", false);
pref("privacy.donottrackheader.enabled", true);
pref("privacy.firstparty.isolate", true);
pref("privacy.resistFingerprinting", false);
pref("webgl.disabled", true);

// telemetry and shield
pref("app.normandy.api_url", "");
pref("app.normandy.enabled", false);
pref("breakpad.reportURL", "");
pref("browser.newtabpage.activity-stream.feeds.telemetry", false);
pref("browser.newtabpage.activity-stream.telemetry", false);
pref("browser.ping-centre.telemetry", false);
pref("browser.tabs.crashReporting.sendReport", false);
pref("datareporting.healthreport.infoURL", "");
pref("datareporting.healthreport.uploadEnabled", false);
pref("datareporting.policy.dataSubmissionEnabled", false);
pref("datareporting.policy.firstRunURL", "");
pref("permissions.manager.defaultsUrl", "");
pref("security.ssl.errorReporting.enabled", false);
pref("security.ssl.errorReporting.url", "");
pref("toolkit.telemetry.archive.enabled", false);
pref("toolkit.telemetry.bhrPing.enabled", false);
pref("toolkit.telemetry.enabled", false);
pref("toolkit.telemetry.firstShutdownPing.enabled", false);
pref("toolkit.telemetry.newProfilePing.enabled", false);
pref("toolkit.telemetry.server", "");
pref("toolkit.telemetry.shutdownPingSender.enabled", false);
pref("toolkit.telemetry.unified", false);
pref("toolkit.telemetry.updatePing.enabled", false);

// addon update check
user_pref("extensions.systemAddon.update.enabled", false);
user_pref("extensions.systemAddon.update.url", "");
user_pref("extensions.update.autoUpdateDefault", false);
user_pref("extensions.update.enabled", false);

// features and media plugins
user_pref("browser.uitour.enabled", false);
user_pref("extensions.formautofill.available", "off");
user_pref("extensions.getAddons.cache.enabled", false);
user_pref("extensions.getAddons.discovery.api_url", "");
user_pref("extensions.htmlaboutaddons.discover.enabled", false);
user_pref("extensions.htmlaboutaddons.recommendations.enabled", false);
user_pref("extensions.pocket.enabled", false);
user_pref("extensions.screenshots.disabled", true);
user_pref("extensions.webcompat-reporter.enabled", false);
user_pref("extensions.webservice.discoverURL", "");
user_pref("identity.fxaccounts.enabled", false);
user_pref("media.eme.enabled", false);
user_pref("media.gmp-gmpopenh264.enabled", false);
user_pref("media.gmp-manager.url", "");
user_pref("media.gmp-provider.enabled", false);
user_pref("media.gmp-widevinecdm.enabled", false);
user_pref("privacy.trackingprotection.cryptomining.enabled", false);
user_pref("privacy.trackingprotection.enabled", false);
user_pref("privacy.trackingprotection.fingerprinting.enabled", false);
user_pref("privacy.trackingprotection.pbmode.enabled", false);
user_pref("webchannel.allowObject.urlWhitelist", "");

// disable google safe browsing
user_pref("browser.safebrowsing.allowOverride", false);
user_pref("browser.safebrowsing.blockedURIs.enabled", false);
user_pref("browser.safebrowsing.downloads.enabled", false);
user_pref("browser.safebrowsing.downloads.remote.block_potentially_unwanted", false);
user_pref("browser.safebrowsing.downloads.remote.block_uncommon", false);
user_pref("browser.safebrowsing.downloads.remote.enabled", false);
user_pref("browser.safebrowsing.downloads.remote.url", "");
user_pref("browser.safebrowsing.provider.mozilla.gethashURL", "");
user_pref("browser.safebrowsing.provider.mozilla.updateURL", "");
user_pref("browser.safebrowsing.malware.enabled", false);
user_pref("browser.safebrowsing.phishing.enabled", false);
user_pref("browser.safebrowsing.reportPhishURL", "");

// mozilla blocklist
pref("extensions.blocklist.enabled", false);
pref("extensions.blocklist.url", "");
pref("services.settings.default_bucket", "");
pref("services.settings.server", "");

// ff defaults
pref("app.update.interval", 86400);
pref("app.update.promptWaitTime", 86400);
pref("app.update.checkInstallTime.days", 2);
pref("app.update.badgeWaitTime", 0);
pref("devtools.selfxss.count", 5);
