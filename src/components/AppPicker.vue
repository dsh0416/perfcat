<template lang="pug">
.app-picker
  h2
    | Perfcat
  el-form(label-width="80px", :model="form")
    el-form-item(:label="t('el.perfcat.backend')")
      el-select(:placeholder="t('el.perfcat.backend')", v-model="form.backend")
        el-option(label="Native" value="native")
    el-form-item(:label="t('el.perfcat.device')")
      el-select(:placeholder="t('el.perfcat.device')")
    el-form-item(:label="t('el.perfcat.application')")
      el-select(:placeholder="t('el.perfcat.application')")
    el-form-item(:label="t('el.perfcat.window')")
      el-select(:placeholder="t('el.perfcat.window')")
    el-form-item(:label="t('el.perfcat.targetFps')")
      el-input-number.fix-height(:min="1" :max="300" :step="1" v-model="form.targetFps")
    el-form-item(:label="t('el.perfcat.actions')")
      el-button(type="primary")
        | {{ t("el.perfcat.submit") }}
      el-button(type="danger")
        | {{ t("el.perfcat.record") }}
</template>

<script lang="ts" setup>
import { reactive } from "vue";
import { useI18n } from "vue-i18n";

/* eslint-disable @typescript-eslint/no-unused-vars */
const { t } = useI18n();
const form = reactive({
  backend: "native",
  device: null,
  application: null,
  window: null,
  targetFps: 60,
});
/* eslint-enable */
</script>

<style lang="stylus" scoped>
.app-picker
  padding 20px

.fix-height // element-ui bug, it goes to 33px by error
  height 32px
</style>
