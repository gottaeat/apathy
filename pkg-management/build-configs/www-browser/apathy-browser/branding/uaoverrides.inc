// defines from default 28.9.0.2
#define GUAO_PREF general.useragent.override
#define GRE_VERSION @MOZILLA_UAVERSION_U@
#define GRE_VERSION_SLICE Goanna/@GRE_VERSION@
#define GRE_DATE_SLICE Goanna/20170101
#define PM_SLICE PaleMoon/@MOZ_APP_VERSION@
#define GK_VERSION @MOZILLA_COMPATVERSION_U@
#define GK_SLICE Gecko/20100101
#define FX_SLICE Firefox/@GK_VERSION@
#define OS_SLICE X11; Linux x86_64;

// apathy-browser overrides
pref("@GUAO_PREF@.pixiv.net", "Mozilla/5.0 (@OS_SLICE@ rv:68.0) Gecko/20100101 Firefox/68.0");
pref("@GUAO_PREF@.deezer.com", "Mozilla/5.0 (@OS_SLICE@ rv:68.0) Gecko/20100101 Firefox/68.0");

// default useragent overrides from 28.9.0.2
pref("@GUAO_PREF@.addons.mozilla.org","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.live.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.msn.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.bing.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.outlook.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.web.de","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.aol.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.calendar.yahoo.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.google.com","Mozilla/5.0 (@OS_SLICE@ rv:71.0) @GK_SLICE@ Firefox/71.0 @PM_SLICE@");
pref("@GUAO_PREF@.googlevideos.com","Mozilla/5.0 (@OS_SLICE@ rv:38.9) @GK_SLICE@ @GRE_VERSION_SLICE@ Firefox/38.9 @PM_SLICE@");
pref("@GUAO_PREF@.gstatic.com","Mozilla/5.0 (@OS_SLICE@ rv:71.0) @GK_SLICE@ Firefox/71.0 @PM_SLICE@");
pref("@GUAO_PREF@.yahoo.com","Mozilla/5.0 (@OS_SLICE@ rv:99.9) @GK_SLICE@ Firefox/99.9 (Pale Moon)");
pref("@GUAO_PREF@.youtube.com","Mozilla/5.0 (@OS_SLICE@ rv:60.0) @GK_SLICE@ Firefox/60.0 @PM_SLICE@");
pref("@GUAO_PREF@.gaming.youtube.com","Mozilla/5.0 (@OS_SLICE@ rv:42.0) @GK_SLICE@ Firefox/42.0");
pref("@GUAO_PREF@.dropbox.com","Mozilla/5.0 (@OS_SLICE@ rv:99.9) @GK_SLICE@ Firefox/99.9 (Pale Moon)");
pref("@GUAO_PREF@.players.brightcove.net","Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko");
pref("@GUAO_PREF@.facebook.com","Mozilla/5.0 (@OS_SLICE@ rv:99.9) @GK_SLICE@ Firefox/99.9 (Pale Moon)");
pref("@GUAO_PREF@.fbcdn.net","Mozilla/5.0 (@OS_SLICE@ rv:99.9) @GK_SLICE@ Firefox/99.9 (Pale Moon)");
pref("@GUAO_PREF@.chase.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@");
pref("@GUAO_PREF@.www.amazon.com","Mozilla/5.0 (@OS_SLICE@ rv:45.9) @GK_SLICE@ Firefox/45.9 (Pale Moon)");
pref("@GUAO_PREF@.soundcloud.com","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.dailymotion.com","Mozilla/5.0 (@OS_SLICE@ rv:52.0) @GK_SLICE@ Firefox/52.0");
pref("@GUAO_PREF@.deviantart.com","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.deviantart.net","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.altibox.dk","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.altibox.no","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.firefox.com","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.mozilla.org","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.mozilla.com","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.github.com","Mozilla/5.0 (@OS_SLICE@ rv:@GRE_VERSION@) @GRE_DATE_SLICE@ @PM_SLICE@");
pref("@GUAO_PREF@.humblebundle.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ (Pale Moon)");
pref("@GUAO_PREF@.privat24.ua","Mozilla/5.0 (@OS_SLICE@ rv:38.0) @GK_SLICE@ Firefox/38.0");
pref("@GUAO_PREF@.citi.com","Mozilla/5.0 (@OS_SLICE@ rv:57.0) @GK_SLICE@ Firefox/57.0 (Pale Moon)");
pref("@GUAO_PREF@.netflix.com","Mozilla/5.0 (@OS_SLICE@ rv:45.9) @GK_SLICE@ Firefox/45.9");
pref("@GUAO_PREF@.netflximg.net","Mozilla/5.0 (@OS_SLICE@ rv:45.9) @GK_SLICE@ Firefox/45.9");
pref("@GUAO_PREF@.web.whatsapp.com","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36");
pref("@GUAO_PREF@.hitbox.tv","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@");
pref("@GUAO_PREF@.yuku.com","Mozilla/5.0 (@OS_SLICE@ rv:@GK_VERSION@) @GK_SLICE@ @FX_SLICE@ @PM_SLICE@");
