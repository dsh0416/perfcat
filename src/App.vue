<template lang="pug">
el-container#main
  el-aside(width="200px") Aside
  el-container
    el-header
      el-menu(mode="horizontal", router, default-active="/")
        el-menu-item(index="/") Performance
        el-menu-item(disabled) Export
        el-menu-item(disabled) Advanced
        el-menu-item(index="/about") About
    el-main
      router-view
</template>

<style lang="stylus">
body
  margin 0

#app
  font-family Avenir, Helvetica, Arial, sans-serif
  -webkit-font-smoothing antialiased
  -moz-osx-font-smoothing grayscale

#main
  width 100%
</style>
