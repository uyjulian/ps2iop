
ifeq (x$(PS2IOPSRC), x)
  export PS2IOPSRC=$(shell pwd)
endif

all:
	make -C iop all

clean:
	make -C iop clean
