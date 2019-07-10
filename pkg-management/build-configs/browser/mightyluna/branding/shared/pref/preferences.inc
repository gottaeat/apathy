// mightyluna
pref("startup.homepage_welcome_url","https://mssx86.github.io/startpage/");
pref("app.vendorURL", "https://github.com/mssx86/mssLinux/");

// --- from base palemoon ---
pref("browser.identity.ssl_domain_display", 1); 

// update and misc (not used but will keep for whatever)
pref("app.update.url", "https://aus.palemoon.org/?application=%PRODUCT%&version=%VERSION%&arch=%BUILD_TARGET%&buildid=%BUILD_ID%&channel=%CHANNEL%");
pref("app.update.download.backgroundInterval", 600);
pref("app.update.promptWaitTime", 172800);
pref("extensions.getMoreThemesURL", "https://addons.palemoon.org/themes/");
pref("extensions.update.autoUpdateDefault", true); // Automatically update extensions by default
pref("extensions.getAddons.maxResults", 10);
pref("extensions.getAddons.cache.enabled", false);
pref("dom.max_chrome_script_run_time", 90); //Some addons need ample time!
pref("dom.max_script_run_time", 20); //Should be plenty for a page script to do what it needs
pref("plugin.default.state", 2); //Allow plugins to run by default
pref("plugin.expose_full_path", true); //Security: expose the full path to the plugin
pref("dom.ipc.plugins.timeoutSecs", 20);
pref("nglayout.initialpaint.delay", 300);
pref("image.mem.max_ms_before_yield", 50);
pref("image.mem.decode_bytes_at_a_time", 65536); //larger chunks
pref("accessibility.force_disabled", 1);
pref("devtools.selfxss.count", 100);

// sync
pref("services.sync.serverURL","https://pmsync.palemoon.org/sync/index.php/");
pref("services.sync.jpake.serverURL","https://keyserver.palemoon.org/");
pref("services.sync.termsURL", "http://www.palemoon.org/sync/terms.shtml");
pref("services.sync.privacyURL", "http://www.palemoon.org/sync/privacy.shtml");
pref("services.sync.statusURL", "https://pmsync.palemoon.org/status/");
pref("services.sync.syncKeyHelpURL", "http://www.palemoon.org/sync/help/recoverykey.shtml");
pref("services.sync.APILevel", 1);
