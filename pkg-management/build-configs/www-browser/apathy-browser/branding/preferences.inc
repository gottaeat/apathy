// set urls
pref("startup.homepage_welcome_url","https://mss.neocities.org/apathy/");
pref("app.vendorURL", "https://github.com/mssx86/apathy");
pref("browser.newtab.choice", 2);
pref("browser.newtab.myhome", "https://mss.neocities.org/startpage/");
pref("browser.newtab.url", "https://mss.neocities.org/startpage/");
pref("browser.newtabpage.storageVersion", 1);

// personal configuration
pref("browser.bookmarks.restore_default_bookmarks", false);
pref("browser.cache.disk.capacity", 102400);
pref("browser.cache.disk.smart_size.enabled", false);
pref("browser.download.dir", "/home/mss/dl");
pref("browser.download.folderList", 2);
pref("browser.download.panel.shown", true);
pref("browser.download.useDownloadDir", true);
pref("browser.feeds.showFirstRunUI", false);
pref("browser.shell.checkDefaultBrowser", false);
pref("browser.tabs.closeWindowWithLastTab", false);
pref("extensions.blocklist.level", 99);
pref("extensions.blocklist.pingCountVersion" 0);
pref("font.default.x-western", "sans-serif");
pref("font.name.monospace.x-western", "xos4 Terminus");
pref("font.name.sans-serif.x-western", "Liberation Sans");
pref("font.name.serif.x-western", "Liberation Sans");
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
pref("status4evar.progress.toolbar.css", "#ff5555");
pref("xpinstall.whitelist.required", true);

// from privacy watchdog
pref("extensions.blocklist.enabled", false);
pref("services.sync.prefs.sync.security.OCSP.enabled", false);
pref("security.OCSP.GET.enabled", false);
pref("security.OCSP.require", false);
pref("security.OCSP.enabled", 0);
pref("geo.enabled", false);
pref("webgl.disabled", "true");
pref("canvas.poisondata", "true");

// pm 28.9.0.2 defaults
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

// disable sync
pref("services.sync.serverURL","");
pref("services.sync.jpake.serverURL","");
pref("services.sync.termsURL", "");
pref("services.sync.privacyURL", "");
pref("services.sync.statusURL", "");
pref("services.sync.syncKeyHelpURL", "");
pref("services.sync.APILevel", 1);
