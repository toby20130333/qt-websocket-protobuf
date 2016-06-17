# (20160617-持续更新)基于nodejs后端框架与Qt前端框架使用protobuf

## 前后端框架模块
* [后端nodejs框架](https://nodejs.org/en/)
* [后端protobuf.js框架](https://github.com/dcodeIO/protobuf.js)
* [前端Qt框架](https://download.qt.io/)
* [谷歌protobuf库](https://github.com/google/protobuf)


### 客户端需求及编译配置
* Qt5.3.1或以上
* 谷歌protobuf3.0beta版本
```
 1 下载QtSDK进行安装即可
 2 自行编译protobuf的C++库及其运行exe(protoc.exe)
 3 Qt中使用protobuf的库 参考pro文件
```

### 服务端需要及编译配置
* nodejsv10.x框架
* protobuf.js框架
* websocket框架
```
 1 下载Nodejs进行安装即可
 2 更新例子下面的package.json即可安装例子所依赖的第三方的包
 3 npm install 即可安装服务端的依赖的包
 4 node server.js
 5 可以打开本地浏览器测试(暂时关闭测试，因为protobuf数据结构问题)
```

## 憧憬

* 实现nodejs后端与Qt前端使用protobuf的数据格式的传输
* 让C++的框架与技术前沿的后端框架进行紧密结合
* 兼容各个主流平台PC客户端的开发



## 贡献

* [寒山-居士](https://github.com/toby20130333)
* [toby520](http://www.heilqt.com)


## 注意事项
* 后端需安装nodejs的sdk，并在命令行使用node -v输出版本查看是否安装正常
* Qt版本必须为5.3.1及以上
* 自己编译protobuf的C++库需要注意编译器的版本与Qt的编译器的版本一致
* 熟练使用protobuf的message结构
* pro文件16行注释说明
```
system(protoc -I=$$PWD --cpp_out=$$PWD $$PWD/*.proto)
表示系统环境变量的protoc指令 将项目当前目录下的proto后缀的文件转成cpp文件即可，
然后将转换后的cpp加入到Qt项目当中即可使用
如下加入:

SOURCES += \
    *.pb.cc

HEADERS += \
    *.pb.h

```
