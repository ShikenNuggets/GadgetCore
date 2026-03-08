FROM archlinux:latest

RUN pacman -Syu --noconfirm

RUN pacman -S --noconfirm \
	base-devel \
	gcc \
	clang \
	git \
	cmake \
	ninja \
