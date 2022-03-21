<template lang="pug">
.app-picker
  h2
    | Perfcat
  el-form(label-width="80px", :model="form")
    el-form-item(:label="t('el.perfcat.backend')")
      el-select(:placeholder="t('el.perfcat.backend')", v-model="form.backend", @change="onFormChange")
        el-option(v-for="backend in candidates.backends", :key="backend.value", :label="backend.name" :value="backend.value")
    el-form-item(:label="t('el.perfcat.device')")
      el-select(:placeholder="t('el.perfcat.device')", v-model="form.device", @change="onFormChange")
        el-option(v-for="device in candidates.devices", :key="device.value", :label="device.name" :value="device.value")
    el-form-item(:label="t('el.perfcat.application')")
      el-select(:placeholder="t('el.perfcat.application')", v-model="form.application", @change="onFormChange")
        el-option(v-for="application in candidates.applications", :key="application.value", :label="application.name" :value="application.value")
    el-form-item(:label="t('el.perfcat.surface')")
      el-select(:placeholder="t('el.perfcat.surface')")
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

import type {
  IApplication,
  IBackend,
  IDevice,
  ISurface,
} from "@/backends/ibackend";
import { MacOsBackend } from "@/backends/macos";

/* eslint-disable @typescript-eslint/no-unused-vars */
const { t } = useI18n();

const candidates = reactive({
  backends: [] as IBackend[],
  devices: [] as IDevice[],
  applications: [] as IApplication[],
  surfaces: [] as ISurface[],
});

const form = reactive({
  backend: "",
  device: "",
  application: "",
  window: "",
  targetFps: 60,
});

const onFormChange = async () => {
  const backend = candidates.backends.filter(
    (a) => a.value === form.backend
  )[0];
  if (backend == null) {
    return;
  }

  candidates.devices = await backend.getDevices();
  const device = candidates.devices.filter((a) => a.value == form.device)[0];
  if (device == null) {
    return;
  }

  candidates.applications = await device.getApplications();
  const application = candidates.applications.filter(
    (a) => a.value == form.application
  )[0];
  if (application == null) {
    return;
  }

  candidates.surfaces = await application.getSurfaces();
};
/* eslint-enable */

candidates.backends = [new MacOsBackend()].filter(
  (backend) => backend.available
);
</script>

<style lang="stylus" scoped>
.app-picker
  padding 20px

.fix-height // element-ui bug, it goes to 33px by error
  height 32px
</style>
