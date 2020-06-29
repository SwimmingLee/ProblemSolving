# 개발자가 알아야될 기술

1. 언어
   1. momory model, thread model, GC 이 어떻게 동작하는지
   2. unitTest, Intergration Test에 대해서 알고 있어야 한다.
   1. unitTest - googletest
         1. 굉징히 믿을만함
   
2. git
3. scipt language 
   1. python
      1. pip로 굉장히 쉽게 라이브러리를 다운받을 수 있다.
      2. 다른 백그란운드 언어로 사용
   2. ruby
   3. 아주 간단한거나 프로토타입을 만들어볼떄 굉장히 유리 
4. Database
   1. data management,
      1. ORM이 잘되어 있어서 아주 다 알 필요 ㄴㄴ
      2. 그러나 ORM이 해결해주지 못하는 것도 있음
      3. 그리고 테이블 나누는 것 알아야 함
      4. 인덱스 설정하는 것도 알아야 함. 이거에 따라서 디비 성능이 달라짐
      5. 인덱스를 정의하는법 쿼리는 O(log(n))안에서 끝나야 함? 
   2. sql vs nosql
      1. 90이상의 상황에서는 sql을 사용할 것
5. web
   1. socket, tcp.utp ㄴㄴ
   2. http, restful api, graphQL이 어떻게 동작하는 지 알아야 함
   
   

1. docker
   1. 다양한 환경을 코드베이스로 관리
2. cloud
	1. aws
	2. azure
3. mobile
   1. 안드로이드
   2. IOS
   3. SDK가 너무 쉽고, 완벽... 개발자로써 포텐셜을 많이 죽이게 된다. 
4. machine learning
   1. 머신 러닝를 이해하면 문제를 이해하기 쉬움. 운영체제 배우는 것같음. 
   2. 문제해결 방법 자체가 달라짐
   3. 앞으로는 점점 대세가 되고 있다.

# 클린코드

early return

- GPU 프로그래밍에서는 무조건 필요
  - cuda는 여러 개의 쓰레드가 동시에 진행 
    - 그래서 thead가 필요하지 않으면 없애줘야 함

룩업 테이블

# 모던 C++ 

## extern vs static

static

- internal linkage

extern

- external linkage

## std::vector

왜 vector를 사용해야 하는가? 

- new, delete를 사용하지 말자 

R-value, L-value란?

- L-value
  - 반복해서 사용할 것 (변수로 된 것)
- R-value
  - 잠깐 사용할 것 

std::move()란?

push_back 보다는 emplace_back를 사용하는 이유는?

struct와 class 차이

object contructor에서 변수 초기화

2차원 배열 접근 방법

캐시를 이용해서 더 빨리 만들자 

## rand()는 사용하지 말자!

rand()의 문제? 균일하지가 않다.!!!

c 다운 소스 

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	rand % 10;
}
```

cpp 다운 소스 

```cpp
#include <ramdom>
int main() {
    std::random_device rd;
	std::mt19937 generator(rd()); // 항상 같은 반복을 원하는 시드를 직접넣어도 됨
    // std::mt19937 gen(12);
    std::uniform_int_disribution<int> distribution(0, 9);
}
```

## std::string

```cpp
std::string a = "abc"
int main() {
	std::cout << sizeof(std::string) << std::endl;
}
```

스탠다드 라이브러리에 따라 사이즈가 다르다!

옛날거는 8btye, modren은 32byte, 40byte이렇게 된다.

32byte이하는 int나 double만큼 스피드가 빨라진다.

cpp 17부터는 string_view가 더 생겼다. 

- read_only 에 관해서만 사용 가능

## singletone

데이터 공간안에 오브젝트를 하나만 선언한다. 

클래스의 생성을 하나의 인스턴스로 제한한다.

모던 랭귀지는 싱글톤을 구현하기 쉽다.

cpp에서는 약간 복잡한 방법을 사용해야 한다. 

cpp singletone을 만드는 법!(구글링)

```cpp
{
public:
    static Singletone& getInstance() {
        static Singleton so;
		return so;
    }
    // copy contructor와 copy assignment를 없애야 함
    Singletone() {}
    Singletone(const Sintgleone&) = delete;
    Singletone& operator=(const Singletone&);
    void printN();
private:
    int n;
}
Singletone Singletone::so;
int main() {
	Singletone& s = Singletone::getInstance();
}
```

## smart pointer

- unique_ptr

  - RAII(Resouce Acquisition is Initialization), scope memory management

    - 리소스를 오브젝트 라이프싸이클과 동기화시킨다.
    - 스코프 베이스로 매니지먼트한다.
    - 유니크 포인터를 사용하므로써 메모리 누수를 방지할 수 있음.

  - Exclusive ownership

    - 하나의 포인터만 ownership을 가리킬 수 있다. 

  - ```cpp
    #include <memory>
    {
        AAA * raw_a = new AAA();
        std::unique_ptr<AAA> a = std::make_unique<AAA>();
        std::unique_ptr<AAA> b = a; // 이건 컴파일 에러(하나의 포인터만 가능)
    }
    ```

- shared_ptr

  - RAII(Resource Acquisition is Initialization)

  - shared ownership

    - ref_count가 있어서 포인터가 몇 개 있는지 관리하는 매커니즘
      - 실재로 자바나 파이썬이 이렇게 관리한다.

  - ```cpp
    std::shared_ptr<AAA> b;
    {
        std::shared_ptr<AAA> a = std::make_shared<AAA>();
        b = a;
    }
    ```

- weak_ptr

  - ref_count를 증가시키거나 감소시키지 않는다.

  - 위크포인터로 쉐어포인터가 살아있는지 검사도 가능

  - ```cpp
    std::weak_ptr<BB> wp;
    std::shated_ptr<BB> a = std::make_shared<BB>();
    wp = a;
    if (auto b = wp.lock()){//object exist}
    else {// no object}
    ```

  - 