<template lang="pug">
el-config-provider(:locale="languageStore.locale")
  el-container#app(:lang="languageStore.lang")
    el-container
      el-aside(width="300px")
        app-picker
      el-container
        el-header
          el-menu(mode="horizontal", router, default-active="/")
            el-menu-item(index="/") 
              | {{ t("el.perfcat.performance") }}
            el-menu-item(disabled)
              | {{ t("el.perfcat.export") }}
            el-menu-item(disabled)
              | {{ t("el.perfcat.advanced") }}
            el-menu-item(index="/about")
              | {{ t("el.perfcat.about") }}
        el-main.main
          router-view
    el-footer
      lang-picker
</template>

<script lang="ts">
import AppPicker from "@/components/AppPicker.vue";
import LangPicker from "@/components/LangPicker.vue";

export default {
  name: "App",
  components: { AppPicker, LangPicker },
};
</script>

<script lang="ts" setup>
import { exec } from "child_process";

import { useI18n } from "vue-i18n";
import { useAlertStore } from "@/stores/alert";
import { useLanguageStore } from "@/stores/language";

const { t } = useI18n();

/* eslint-disable @typescript-eslint/no-unused-vars */
const languageStore = useLanguageStore();
/* eslint-enable */

// macOS Requires SIP disabled for frida hook working.
if (process.platform === "darwin") {
  exec("csrutil status", (_0, stdout, _2) => {
    if (stdout === "System Integrity Protection status: enabled.\n") {
      const alerts = useAlertStore();
      alerts.alert(t("el.perfcat.sipError"), "error");
    }
  });
}
</script>

<style lang="stylus">
body
  font-family Avenir, Helvetica, Arial, sans-serif
  -webkit-font-smoothing antialiased
  -moz-osx-font-smoothing grayscale
  background #ffffff
  margin 0

#app
  width 100%
  min-height 100vh
</style>
