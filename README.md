About
=====

This is a Arduino add-on package which use [Zephyr OS](https://www.zephyrproject.org/) as backend and develop with Arduino API.

Install
=======

Install Arduino on Zephyr plugin
--------------------------------

Use this additional package definition of 'Additional Boards Manager URLs' option that is on Arduino's preferences.
* [https://soburi.github.io/arduino-on-zephyr/package_soburi_scirocco_index.json](https://soburi.github.io/arduino-on-zephyr/package_soburi_scirocco_index.json)

Build environment setup
----------------------------

Read [Set Up a Development System](https://docs.zephyrproject.org/latest/getting_started/index.html#set-up-a-development-system) instructions.

On Debian/Ubuntu system, run this commands.

```
sudo apt-get install --no-install-recommends git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-pip python3-setuptools python3-wheel xz-utils file make gcc \
  gcc-multilib

sudo apt-get install --no-install-recommends automake libtool

pip3 install -r <(wget https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/master/scripts/requirements.txt)
pip3 install west

wget https://github.com/zephyrproject-rtos/meta-zephyr-sdk/releases/download/0.9.5/zephyr-sdk-0.9.5-setup.run
chmod +x zephyr-sdk-0.9.5-setup.run
sudo ./zephyr-sdk-0.9.5-setup.run --target /opt/zephyr-sdk/ -- -y -d /opt/zephyr-sdk/
```


Limitations
===========

This package is under _EARLY_ develpment stage.
