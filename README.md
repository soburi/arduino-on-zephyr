THIS PROJECT IS ARCHIVED
========================

All achivements of this project have been merged into [https://github.com/zephyrproject-rtos/gsoc-2022-arduino-core](https://github.com/zephyrproject-rtos/gsoc-2022-arduino-core). Please use them.

-------------------------------------------------------------------------------

About
=====

This is a Arduino package which able to develop with Arduino API with using [Zephyr RTOS](https://www.zephyrproject.org/) as base system.

This source code can also use as a module for Zephyr.

Install
=======

Install from ArduinoIDE
--------------------------------

Use this additional package definition of 'Additional Boards Manager URLs' option that is on Arduino's preferences.
* [https://soburi.github.io/arduino-on-zephyr/package_soburi_scirocco_index.json](https://soburi.github.io/arduino-on-zephyr/package_soburi_scirocco_index.json)

Use as a Zephyr Module
--------------------------------

To use this module download(clone) `zephyr` source and configure `west.yml`.
Append lines to `remotes` and `projects` section to `west.yml` like a below.

```
manifest:
  defaults:
    remote: upstream

  remotes:
    - name: upstream
      url-base: https://github.com/zephyrproject-rtos
    - name: soburi                                        # ADD
      url-base: https://github.com/soburi                 # ADD
  #
  # Please add items below based on alphabetical order
  projects:
    - name: arduino-on-zephyr                             # ADD
      revision: scirocco-0.0.20200210                     # ADD
      path: modules/lib/arduino-on-zephyr                 # ADD
      remote: soburi                                      # ADD
    - name: hal_atmel
      revision: 5a44c9d54dffd685fb6664a646922cfe41c5cf8e
      path: modules/hal/atmel
  ........ snip  ........
```

And run command in below to fetch modules.

```
west init -l zephyr
west update
```

See a example in [https://github.com/soburi/zephyr/tree/arduino-example](https://github.com/soburi/zephyr/tree/arduino-api-example) for using this module.

Build environment setup
----------------------------

Read [Set Up a Development System](https://docs.zephyrproject.org/latest/getting_started/index.html#set-up-a-development-system) instructions.

In summary,
- Install OS packages and python dependencies
- Install `zephyr-sdk`
- Install `west` (Don't forget append `.local/bin` to `PATH`)

Limitations
===========

This package is under _EARLY_ develpment stage.
