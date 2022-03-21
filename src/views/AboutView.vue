<template lang="pug">
.about
  h1
    | Perfcat 
  p
    | Version: v{{ version }}_{{ arch }}
  p
    | Proudly made with ❤️ by Delton Ding.
</template>

<script lang="ts" setup>
import { app } from "@electron/remote";

/* eslint-disable @typescript-eslint/no-unused-vars */
const arch = `${process.platform}_${process.arch}`;
const version = app.getVersion();
/* eslint-enable */
</script>

<style lang="stylus" scoped>
.about
  text-align center
  padding-top 50px
</style>
