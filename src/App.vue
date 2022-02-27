<template lang="pug">
el-config-provider(:locale="languageStore.locale")
  el-container#app(:lang="languageStore.lang")
    el-container
      el-aside(width="300px")
        app-picker
      el-container
        el-header
          el-menu(mode="horizontal", router, default-active="/")
            el-menu-item(index="/") Performance
            el-menu-item(disabled) Export
            el-menu-item(disabled) Advanced
            el-menu-item(index="/about") About
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
import { useLanguageStore } from "@/stores/language";

/* eslint-disable @typescript-eslint/no-unused-vars */
const languageStore = useLanguageStore();
/* eslint-enable */
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
