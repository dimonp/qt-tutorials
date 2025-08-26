FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

ARG USERNAME=ubuntu

# Add sudo support.
RUN apt-get update && \
    apt-get install -y sudo && \
    echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

RUN apt-get update && apt-get -y install \
# Essential packages to build and link to right libraries
    build-essential git cmake extra-cmake-modules ninja-build \
    automake autoconf libtool pkg-config \
    clang clang-tools clangd clang-tidy clang-format \
    gdb ccache bash locales \
    wget 7zip \
    && apt-get clean \
    && apt-get -y autoremove --purge \
    && rm -rf /var/lib/apt/lists/*

RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && \
    locale-gen en_US.UTF-8 && \
    update-locale LANG=en_US.UTF-8

ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

RUN apt-get update && apt-get -y install \
    apt-transport-https ca-certificates gnupg2 \
    mesa-common-dev meson libclang-dev \
    libdbus-1-dev libxkbcommon-x11-dev \
    libfontconfig1-dev libfreetype6-dev \
    libxext-dev libxfixes-dev libxi-dev libxrender-dev \
    freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev \
    libvulkan-dev libssl-dev libglib2.0-dev \
    mesa-vulkan-drivers lsb-release \
    libatspi2.0-dev libwayland-dev \
    xserver-xorg-dev xorg-dev \
    libegl1-mesa-dev libgles2-mesa-dev \
    libx11-* libx11* libxcb-* libxcb* libxkb* \
    ffmpeg libavcodec-dev libavformat-dev libavutil-dev bluez \
    libwebp-dev libbluetooth-dev nodejs \
    python3-dev python3-html5lib gperf \
    bison flex libnss3* libxshmfence-dev libcups2-dev \
    ffmpeg libpulse-dev libasound2-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libavcodec-dev libavfilter-dev libvpx-dev \
    libopus-dev libx264-dev libx265-dev libmp3lame-dev libvorbis-dev libtheora-dev libspeex-dev libopenal-dev libsndfile1-dev \
    libflac-dev libogg-dev libopusfile-dev libmodplug-dev libmpg123-dev libsndio-dev libwavpack-dev libfaad-dev libgsm1-dev libdv4-dev \
    libproxy-dev libkrb5-dev libicu-dev zlib1g-dev \
    && apt-get clean \
    && apt-get -y autoremove --purge \
    && rm -rf /var/lib/apt/lists/*

USER $USERNAME

WORKDIR /home/$USERNAME
RUN git clone https://github.com/qt/qt5.git qt6

ARG QT_VERSION=6.8.3
ENV QT_VERSION=${QT_VERSION}

WORKDIR /home/$USERNAME/qt6
RUN git switch ${QT_VERSION} && perl init-repository

ARG QT_CONFIG_ARGS="-skip qtwebengine -nomake examples -nomake tests -developer-build -opensource -confirm-license"

RUN mkdir build
WORKDIR /home/$USERNAME/qt6/build
RUN ../configure -prefix /opt/qt-$QT_VERSION $QT_CONFIG_ARGS
RUN cmake --build . --parallel 4
USER root
RUN cmake --install . \
    && rm -rf /home/$USERNAME/qt6/build

ENV QT_DIR="/opt/qt-$QT_VERSION"
ENV Qt6_DIR="/opt/qt-$QT_VERSION/lib/cmake/Qt6"
ENV CMAKE_PREFIX_PATH="/opt/qt-$QT_VERSION/lib/cmake"
ENV PATH="$PATH:/opt/qt-$QT_VERSION/bin"

WORKDIR /opt
RUN wget https://github.com/qt-creator/qt-creator/releases/download/v16.0.2/qtcreator-linux-x64-16.0.2.7z \
    && 7z x qtcreator-linux-x64-16.0.2.7z -oqtcreator16 \
    && rm qtcreator-linux-x64-16.0.2.7z
ENV PATH="$PATH:/opt/qtcreator16/bin"

ENV XDG_RUNTIME_DIR=/tmp

WORKDIR /workspace
RUN chmod 755 /workspace

USER $USERNAME
