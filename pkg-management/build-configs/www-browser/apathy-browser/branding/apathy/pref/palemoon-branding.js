#filter substitution
#filter emptyLines

#define GUAO_PREF general.useragent.override

// act as firefox 52-esr by default
pref("@GUAO_PREF@",             "Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0");

// site specific overrides
pref("@GUAO_PREF@.pixiv.net",   "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
pref("@GUAO_PREF@.deezer.com",  "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
pref("@GUAO_PREF@.github.com",  "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");

// disable updates
pref("app.update.enabled", false);
pref("app.update.url", "");

// set urls
pref("startup.homepage_welcome_url","https://github.com/mssx86/apathy");
pref("startup.homepage_override_url","https://github.com/mssx86/apathy");
pref("app.releaseNotesURL", "https://github.com/mssx86/apathy");
pref("app.vendorURL", "https://github.com/mssx86/apathy");
pref("browser.newtab.choice", 2);
pref("browser.newtab.myhome", "about:blank");
pref("browser.newtab.url", "about:blank");
pref("browser.newtabpage.storageVersion", 1);

// personal configuration
pref("browser.bookmarks.restore_default_bookmarks", false);
pref("browser.cache.disk.capacity", 30720);
pref("browser.cache.disk.smart_size.enabled", false);
pref("browser.cache.disk.smart_size.first_run", false);
pref("browser.cache.disk.smart_size.use_old_max", false);
pref("browser.display.use_document_fonts", 0);
pref("browser.download.dir", "/home/mss/dl");
pref("browser.download.folderList", 2);
pref("browser.download.panel.shown", true);
pref("browser.download.useDownloadDir", true);
pref("browser.feeds.showFirstRunUI", false);
pref("browser.pagethumbnails.storage_version", 3);
pref("browser.places.smartBookmarksVersion", 4);
pref("browser.preferences.advanced.selectedTabIndex", 1);
pref("browser.preferences.privacy.selectedTabIndex", 0);
pref("browser.shell.checkDefaultBrowser", false);
pref("browser.tabs.closeWindowWithLastTab", false);
pref("extensions.blocklist.level", 99);
pref("extensions.blocklist.pingCountVersion", 0);
pref("font.default.x-western", "sans-serif");
pref("font.name.monospace.x-western", "xos4 Terminus");
pref("font.name.sans-serif.x-western", "Liberation Sans");
pref("font.name.serif.x-western", "Liberation Sans");
pref("font.name.monospace.ja", "xos4 Terminus");
pref("font.name.sans-serif.ja", "xos4 Terminus");
pref("font.name.serif.ja", "xos4 Terminus");
pref("general.smoothScroll", false);
pref("general.smoothScroll.lines", false);
pref("general.smoothScroll.mouseWheel", false);
pref("general.smoothScroll.pages", false);
pref("general.smoothScroll.scrollbars", false);
pref("general.warnOnAboutConfig", false);
pref("layers.acceleration.enabled", true);
pref("layers.acceleration.force", true);
pref("middlemouse.contentLoadURL", false);
pref("pref.privacy.disable_button.view_passwords", false);
pref("privacy.donottrackheader.enabled", true);
pref("signon.autofillForms", true);
pref("xpinstall.whitelist.required", true);

// from privacy watchdog
pref("extensions.blocklist.enabled", false);
pref("services.sync.prefs.sync.security.OCSP.enabled", false);
pref("security.OCSP.GET.enabled", false);
pref("security.OCSP.require", false);
pref("security.OCSP.enabled", 0);
pref("geo.enabled", false);
pref("canvas.poisondata", "true");

// sync
pref("services.sync.serverURL","https://pmsync.palemoon.org/sync/index.php/");
pref("services.sync.jpake.serverURL","https://keyserver.palemoon.org/");
pref("services.sync.termsURL", "http://www.palemoon.org/sync/terms.shtml");
pref("services.sync.privacyURL", "http://www.palemoon.org/sync/privacy.shtml");
pref("services.sync.statusURL", "https://pmsync.palemoon.org/status/");
pref("services.sync.syncKeyHelpURL", "http://www.palemoon.org/sync/help/recoverykey.shtml");
pref("services.sync.APILevel", 1); // FSyncMS doesn't support 'info/configuration' requests

// pm 28.9.13
pref("browser.identity.ssl_domain_display", 1);
pref("app.update.download.backgroundInterval", 600);
pref("app.update.promptWaitTime", 172800);
pref("extensions.getMoreThemesURL", "https://addons.palemoon.org/themes/");
pref("extensions.update.autoUpdateDefault", true);
pref("extensions.getAddons.maxResults", 10);
pref("extensions.getAddons.cache.enabled", false);
pref("dom.max_chrome_script_run_time", 90);
pref("dom.max_script_run_time", 20);
pref("plugin.default.state", 2);
pref("plugin.expose_full_path", true);
pref("dom.ipc.plugins.timeoutSecs", 20);
pref("nglayout.initialpaint.delay", 300);
pref("image.mem.max_ms_before_yield", 50);
pref("image.mem.decode_bytes_at_a_time", 65536);
pref("accessibility.force_disabled", 1);
pref("devtools.selfxss.count", 100);
