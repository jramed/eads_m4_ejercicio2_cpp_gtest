FROM gcc:6.1.0

RUN apt-get update && \
    apt-get install -y cmake

RUN cd /home && \
    mkdir googleTestMock && \
    cd googleTestMock && \
    wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz -O googletest-release-1.7.0.tar.gz && \
    wget https://github.com/google/googlemock/archive/release-1.7.0.tar.gz -O googlemock-release-1.7.0.tar.gz && \
    tar -zxvf googletest-release-1.7.0.tar.gz && \
    mv googletest-release-1.7.0 gtest && \
    tar -zxvf googlemock-release-1.7.0.tar.gz && \
    cd googlemock-release-1.7.0 && \
    cmake . && \
    make && \
    mv libg* /usr/lib && \
    cp -r ./include/gmock /usr/include/gmock && \
    cp -r ../gtest/include/gtest /usr/include/gtest && \
    mv gtest/libg* /usr/lib && \
    rm -rf /home/googleTestMock
