# On some computers it takes a long time to flash the board,
# so we need to increase the delay.
PREFLASH_DELAY=10

# The ZTIMER_MSEC seems to be broken on some compilers so we force docker
# to ensure a working compiler.
# We also want to make sure the we are not doing any docker in docker
# shenanigans.
USER=$(shell whoami)
ifneq ($(USER),riotbuild)
  export BUILD_IN_DOCKER=1
endif