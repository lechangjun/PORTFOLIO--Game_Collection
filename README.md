# PORTFOLIO_SGA

## SGA 포폴 정리 시작 (2021/04/19)
### 부족한점 보완
* 2021 06 24 -> C++ 자료 구조 및 STL 추가 학습
* 2021 06 28 -> Directx_2D 공부 시작 (벡터 && 렌더링 파이프라인)



## 1.


## 2.



* **CallStack** - Gain code-level visibility to every transaction in a distributed environment, identifying bottlenecks and points of failure in a single view.

  ![Call Stack](doc/images/ss_call-stack.png)

* **Inspector** - View additional details on the application such as CPU usage, Memory/Garbage Collection, TPS, and JVM arguments.

  ![Inspector](doc/images/ss_inspector.png)




## Compatibility

Java version required to run Pinpoint:

Pinpoint Version | Agent | Collector | Web
---------------- | ----- | --------- | ---
1.7.x  | 6-8  | 8   | 8
1.8.0  | 6-10 | 8   | 8 
1.8.1+ | 6-11 | 8   | 8 
2.0.x  | 6-13 | 8   | 8
2.1.x  | 6-14 | 8   | 8
2.2.x  | 7-14 | 8   | 8
2.3.x  | 7-17 | 8   | 8

HBase compatibility table:

Pinpoint Version | HBase 1.0.x | HBase 1.2.x | HBase 1.4.x | HBase 2.0.x
---------------- | ----------- | ----------- | ----------- | -----------
1.7.x | not tested | yes | yes | no
1.8.x | not tested | yes | yes | no
2.0.x | not tested | yes | yes | [optional](https://pinpoint-apm.github.io/pinpoint/hbaseupgrade.html#do-you-like-to-use-hbase-2x-for-pinpoint)
2.1.x | not tested | yes | yes | [optional](https://pinpoint-apm.github.io/pinpoint/hbaseupgrade.html#do-you-like-to-use-hbase-2x-for-pinpoint)
2.2.x | not tested | yes | yes | [optional](https://pinpoint-apm.github.io/pinpoint/hbaseupgrade.html#do-you-like-to-use-hbase-2x-for-pinpoint)
2.3.x | not tested | yes | yes | [optional](https://pinpoint-apm.github.io/pinpoint/hbaseupgrade.html#do-you-like-to-use-hbase-2x-for-pinpoint)

Agent - Collector compatibility table:

Agent Version | Collector 1.7.x | Collector 1.8.x | Collector 2.0.x | Collector 2.1.x | Collector 2.2.x | Collector 2.3.x |
------------- | --------------- | --------------- | --------------- | --------------- | --------------- | --------------- |
1.7.x | yes | yes | yes | yes | yes | yes 
1.8.x | no  | yes | yes | yes | yes | yes 
2.0.x | no  | no  | yes | yes | yes | yes 
2.1.x | no  | no  | no  | yes | yes | yes 
2.2.x | no  | no  | no  | no  | yes | yes
2.3.x | no  | no  | no  | no  | no  | yes

Flink compatibility table:

Pinpoint Version | flink 1.3.X | flink 1.4.X | flink 1.5.X | flink 1.6.X | flink 1.7.X
---------------- | ----------- | ----------- | ----------- | ----------- | ----------- 
1.7.x | yes | yes | no | no | no |
1.8.x | yes | yes | no | no | no |
2.0.x | yes | yes | yes | yes | yes |
2.1.x | yes | yes | yes | yes | yes |
2.2.x | yes | yes | yes | yes | yes |
2.3.x | yes | yes | yes | yes | yes |


## Community


## License


