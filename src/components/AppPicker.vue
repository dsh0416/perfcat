<template lang="pug">
.app-picker
  h2
    | Perfcat
  el-form(label-width="80px")
    el-form-item(label="Backend")
      el-select(placeholder="Backend")
        el-option(label="macOS" value="native")
    el-form-item(label="Device")
      el-select(placeholder="Device")
    el-form-item(label="Application")
      el-select(placeholder="Application")
    el-form-item(label="Surface")
      el-select(placeholder="Surface")
    el-form-item(label="Target FPS")
      el-input-number.fix-height(:min="1" :max="300" :step="1" v-model="val")
    el-form-item(label="Actions")
      el-button(type="primary") Submit
      el-button(type="danger") Record
</template>

<script lang="ts" setup>
/* eslint-disable @typescript-eslint/no-unused-vars */
const val = 60;
/* eslint-enable */
</script>

<style lang="stylus" scoped>
.app-picker
  padding 20px

.fix-height // element-ui bug, it goes to 33px by error
  height 32px
</style>
