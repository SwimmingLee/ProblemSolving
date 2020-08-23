# 문제 풀이 접근별로 정리



## Simulation

- [경사로](https://www.acmicpc.net/problem/14890) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/Simulation/%5BBOJ_14890%5D%EA%B2%BD%EC%82%AC%EB%A1%9C.cpp)
	
  - 경로를 탐색하면서 경사로를 추가하여 이동할 수 있는 길이 되는지 확인하는 문제이다. 오르막인지, 내리막인지 여부에 따라 경사로를 놓을 수 있는 지 판단하여 풀 수 있다.
  
    


## Brute Force 

### NandM

- [N과 M(1)](https://www.acmicpc.net/problem/15649)
- [N과 M(2)](https://www.acmicpc.net/problem/15650)
- [N과 M(3)](https://www.acmicpc.net/problem/15651)
- [N과 M(4)](https://www.acmicpc.net/problem/15652)
- [N과 M(5)](https://www.acmicpc.net/problem/15654)
- [N과 M(6)](https://www.acmicpc.net/problem/15655)
- [N과 M(7)](https://www.acmicpc.net/problem/15656)
- [N과 M(8)](https://www.acmicpc.net/problem/15657)
- [N과 M(9)](https://www.acmicpc.net/problem/15663)
- [N과 M(10)](https://www.acmicpc.net/problem/15664)
- [N과 M(11)](https://www.acmicpc.net/problem/15665)
- [N과 M(12)](https://www.acmicpc.net/problem/15666)



### Two Pointers Algorithms

- [수들의 합2](https://www.acmicpc.net/problem/2003)

- [소수의 연속합](https://www.acmicpc.net/problem/1644)

- [부분합](https://www.acmicpc.net/problem/1806)
- [소수의 연속합](https://www.acmicpc.net/problem/1644)
- [부분집합의 합 2](https://www.acmicpc.net/problem/1208)
- [두 배열의 합](https://www.acmicpc.net/problem/2143)
- [합이 0인 네 정수](https://www.acmicpc.net/problem/7453)



### BruteForce

- [종이조각](https://www.acmicpc.net/problem/14391)  [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/BruteForce/%5BBOJ_14391%5D%EC%A2%85%EC%9D%B4%20%EC%A1%B0%EA%B0%81.cpp) :star: 
	- 종이조각을 자르는 방식은 가로로 자르거나 세로로 자르거나 둘 중 하나이다. 주어진 보드판의 크기가 최대 4x4이기때문에 **비트마스크**를 사용하여 모두 탐색할 수 있다.
- [차량 번호판 1](https://www.acmicpc.net/problem/16968) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/BruteForce/%5BBOJ_16968%5D%EC%B0%A8%EB%9F%89%20%EB%B2%88%ED%98%B8%ED%8C%90%201.cpp)
  - 연속되는 숫자가 나오지 않는 경우의 수를 세는 문제이다. 
- [양념 반 후라이드 반](https://www.acmicpc.net/problem/16917) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/BruteForce/%5BBOJ_16917%5D%EC%96%91%EB%85%90%20%EB%B0%98%20%ED%9B%84%EB%9D%BC%EC%9D%B4%EB%93%9C%20%EB%B0%98.cpp)
  - 수식을 이용해서 한 번에 최적해를 구할 수 있지 않을 까 했지만, 오산이였다. (반마리를 여러 개 사면 정해진 조건보다 치킨의 양이 초과되지만 가격이 싸지는 경우가 있음) 반마리 치킨의 개수를 완전탐색으로 조절해가며 가장 싼 가격을 구하는 문제이다.
- [로마 숫자 만들기](https://www.acmicpc.net/problem/16922) :star:
  - 규칙을 파악해서 한 번에 최적해를 구할 수 있을까 했지만, 착각이였다. 이런 문제들은 먼저 탐색 크기를 보고, 가능하다 싶으면 완전 탐색으로 구하도록 하자.
- [십자가 찾기](https://www.acmicpc.net/problem/16924) 
  - 주어진 그림과 같이 만들 수 있도록 하는 십자가를 구하는 문제이다. 최소한의 십자가를 구하는 것이 아니라 정답이 될 수 있는 십자가를 출력하는 문제이기 때문에 모든 요소에서 사방으로 얼마나 별이 있는지 개수를 세주면 풀 수 있는 문제이다.
- [나3곱2](https://www.acmicpc.net/problem/16936) :star::star:
  - 수열의 크기가 100이라서 가능한 모든 순서를 탐색해서 진행한다면 최악의 경우 O(N!)이기 때문에 터질 수 밖에 없습니다. 이 문제는 약간의 아이디어로 O(NlogN)만에 풀 수 있습니다. 나누기3이라는 요소 때문에 수열 속의 약수가 3의 배수가 높은 순서대로 나올 수 밖에 없습니다. 즉, 3^n, 3^(n-1), 3^(n-2)식으로 나올 수 밖에 없습니다. 마찬가지로 각 2의 배수는 증가하는 쪽으로 밖에 수열이 이뤄질 수가 있습니다. 이러한 특징을 이용해서 정렬한다면 O(NlogN)만에 풀 수 있는 문제입니다. 
- [두 스티커](https://www.acmicpc.net/problem/16937) :star:
  - 여러 개의 스터커 중에서 임의의 두 개의 스티커를 붙였을 때 붙인 부분의 넓이가 가장 큰 것을 구하는 문제입니다. 두 개의 스티커를 가능한 넓게 붙이기 위해서는 첫 번째 스티커를 왼쪽위에 붙이고 다른 스티커는 첫 번째 스티커와 인접하는 오른쪽 위 또는 왼쪽 아래에다가 붙여야 합니다. 따라서 상수시간만에 스티커를 부착시킬 수 있는지 확인할 수 있습니다. N이 최대 100이기 때문에 스티커를 선별하는 경우의 수는 100C2로 충분히 제한 시간 내에 풀 수 있습니다. 
- [캠프 준비](https://www.acmicpc.net/problem/16938)
  - 각 문제를 고르느냐, 고르지 않느냐를 선별하는 문제로 바꿔 생각할 수 있습니다. N이 최대 15이므로 최대 경우의 수는 2^15, 충분히 제한 시간 내에 풀 수 있습니다.
- [치킨 배달]()(https://www.acmicpc.net/problem/15686)
  - 조합을 이용해서 풀 수 있는 문제입니다. 조합을 하면서 앞으로 가능한 것의 갯수와 앞으로 선택해야 되는 것의 갯수를 비교해서 중간에 가지를 쳐내도 백준 알고리즘 사이트상에서 실행시간은 동일하게 4ms네요.조합을 이용해서 풀 수 있는 문제이기 때문에 앞으로는 더 빨리 풀 수 있도록 노력해야 겠습니다.
- [숫자 재배치](https://www.acmicpc.net/problem/16943)
- [괄호 추가하기](https://www.acmicpc.net/problem/16637) 
- [감시](https://www.acmicpc.net/problem/15683)
- [등차수열 변환](https://www.acmicpc.net/problem/17088) :star::star:
- [치킨 배달](https://www.acmicpc.net/problem/15686)
- [숫자판 점프](https://www.acmicpc.net/problem/2210)
- [테트리스](https://www.acmicpc.net/problem/3019)
- [한윤정이 이탈리아에 가서 아이스크림을 사먹는데](https://www.acmicpc.net/problem/2422)
- [NxM 보드 완주하기](https://www.acmicpc.net/problem/9944)
- [세 친구](https://www.acmicpc.net/problem/17089)
- [배열 돌리기 4](https://www.acmicpc.net/problem/17406)
- [파이프 옮기기 1](https://www.acmicpc.net/problem/17070)
- [파이프 옮기기 2](https://www.acmicpc.net/problem/17069)
- [괄호 추가하기 2](https://www.acmicpc.net/problem/16638)
- [십자가 2개 놓기](https://www.acmicpc.net/problem/17085)
- [계란으로 계란치기](https://www.acmicpc.net/problem/16987)
- [Baaaaaaaaaduk2 (Easy)](https://www.acmicpc.net/problem/16988)
- [사다리 조작](https://www.acmicpc.net/problem/15684)
- [삼각형의 값](https://www.acmicpc.net/problem/4902)
- [매직 스퀘어로 변경하기](https://www.acmicpc.net/problem/16945)
- [A → B](https://www.acmicpc.net/problem/16953)
- [Maaaaaaaaaze](https://www.acmicpc.net/problem/16985)
- [인싸들의 가위바위보](https://www.acmicpc.net/problem/16986)
- [미로 탈출하기](https://www.acmicpc.net/problem/17090)
- [두 배 더하기](https://www.acmicpc.net/problem/12931)
- [텔레포트](https://www.acmicpc.net/problem/16958)
- [텔레포트 3](https://www.acmicpc.net/problem/12908)
- [체스판 위의 공](https://www.acmicpc.net/problem/16957)
- [배열 B의 값](https://www.acmicpc.net/problem/16971)



## Graph

### 위상정렬

- [문제집](https://www.acmicpc.net/problem/1766) :star:

- [문제집](https://www.acmicpc.net/problem/1766)
- [작업](https://www.acmicpc.net/problem/2056)

- 게임 개발 :star:
  - 위상정렬의 기본적인 문제
  - 시간을 고려하기 때문에 우선순위를 판별해 주는 것이 필요함 

### DFS 

- [가르침](https://www.acmicpc.net/problem/1062) :star: :star: #다시 풀 것!
  
  - 제한된 알파벳을 학습시켜 최대한의 단어를 이해시키는 문제이다.  학습시킨 알파벳만으로 단어를 이해할 수 있는지 확인할 때 **비트마스크**를 사용하면 O(1)만에 확인할 수 있다.
  
- [퇴사](https://www.acmicpc.net/problem/14501) :star:#다시 풀 것!
  
  -  상담을 할 것인지 말 것인지를 선택하여 모든 경우의 수를 DFS를 통해서 구할 수 있다.
  
- [N-Queen](https://www.acmicpc.net/problem/9663) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/DFS/%5BBOJ_9663%5DN-Queen.cpp) :star:

  - 보드판의 크기에 따라 모든 행에 퀸이 등장할 수 있는 경우의 수를 출력하는 문제이다. **백트래킹**을 이용하여 풀 수 있다. 퀸이 등장해야하는지 아닌지는 체크배열을 통해 O(1)만에도 확인할 수 있다.

    


### BFS

- [개리먼더링](https://www.acmicpc.net/problem/17471) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/BFS/%5BBOJ_17471%5D%EA%B2%8C%EB%A6%AC%EB%A7%A8%EB%8D%94%EB%A7%81.cpp) :star:
  
  - 모든 지역을 두 개의 선거구으로 구분할 때, 인원의 차이가 최소가 되도록 하는 문제이다.  각 지역은 선거구A또는 선거구B 상태를 가짐으로 **비트마스크**를 사용하여 **완전탐색**할 수 있다. 
- [욕심쟁이 판다](https://www.acmicpc.net/problem/1937)
  - BFS와 DP를 같이 써야지만 풀 수 있는 문제. 종만북에 나와있는 DP 모양을 그대로 사용해서 해결할 수 있다.
- [늑대와 양](https://www.acmicpc.net/problem/16956)
- [스타트링크](https://www.acmicpc.net/problem/5014)
- [탈옥](https://www.acmicpc.net/problem/9376) :star::star::star:
- [물통](https://www.acmicpc.net/problem/2251)
- [모양 만들기](https://www.acmicpc.net/problem/16932)
- [말이 되고픈 원숭이](https://www.acmicpc.net/problem/1600) :star:
- [아기 상어 2](https://www.acmicpc.net/problem/17086)
- [로봇 청소기](https://www.acmicpc.net/problem/4991)
- [거울 설치](https://www.acmicpc.net/problem/2151)
- [성곽](https://www.acmicpc.net/problem/2234)
- [새로운 하노이 탑](https://www.acmicpc.net/problem/12906)
- [연구소 2](https://www.acmicpc.net/problem/17141)
- [연구소 3](https://www.acmicpc.net/problem/17142)





## Data Instruction

### Stack

- [문자열 폭발](https://www.acmicpc.net/problem/9935)  [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/DataInstuction/%5BBOJ_9935%5D%EB%AC%B8%EC%9E%90%EC%97%B4%20%ED%8F%AD%EB%B0%9C.cpp) :star:
  - 두 개의 스택을 이용하여 문자열이 폭발할 때 해당 글자를 제거해주면 되는 문제이다. 
- [오큰수](https://www.acmicpc.net/problem/17298)
- [오등큰수](https://www.acmicpc.net/problem/17299)
- [히스토그램에서 가장 큰 직사각형](https://www.acmicpc.net/problem/6549) :star::star::star:
  - 분할정복을 이용하면 O(NlogN)만에 풀 수 있지만, 스위핑 알고리즘과 스택을 이용하면 O(N)만에 풀 수 있는 문제입니다. **스위핑 알고리즘**은 어떤 선이나 공간을 한쪽에서부터 싹 쓸어버린는 형태를 가집니다. 그래서 한 번만 전체 공간을 스캔하면서 마주치는 요서들에 대해 뭔가를 해주면 정답을 구할 수 있는 문제입니다. 개념적으로는 간단하다고 느끼기 쉽지만, 아이디어를 생각해기 굉장히 어렵습니다. 기본적으로 다른 기법이나 자료구조와 얽히기 때문에 더욱 까다록게 느껴집니다. **스택 마지막 처리** 유심히 살펴봐야 합니다.
- [오아시스 재결합](https://www.acmicpc.net/problem/3015) :star::star::star:
  - 완전탐색하려면 O(N^2)이 걸린다. 이런 문제는 바로 **스위핑 알고리즘**을 적용하려고 하지 말고 먼저 완전 탐색으로 풀라고 해보자. 완전 탐색으로 해서 풀리지 않는다는 것을 알고 있지만, 이렇게 해야 논리가 명확해 질 수 있다.  



### Queue



### Union-Find

- [집합의 표현](https://www.acmicpc.net/problem/1717) :star:
  - 두 요소가 서로 같은 집합에 있는지 물어보는 문제이다. 유니온-파인드를 쓰서 집합을 연결해주고 부모노드를 찾는다면 제한 시간 내에서 빠르게 풀 수 있는 문제이다.
- [바이러스](https://www.acmicpc.net/problem/2606)
  - DFS/BFS로도 풀 수 있고, 유니온-파인드로도 풀 수 있는 문제이다. 
- [여행가자](https://www.acmicpc.net/problem/1976)
  - 동혁이의 계획대로 여행이 가능한지 아닌지를 판별하는 문제입니다. 길이 연결되어있다면 어떻게든 여행을 할 수 있으므로, 여행계획 도시들이 모두 연결되어있는 집합안에 있는지 판별하면 풀 수 있는 문제입니다.
- [친구비](https://www.acmicpc.net/problem/16562)
  - 서로 친한 친구들끼리 그룹을 만들고, 친구 그룹들을 순회하면서 풀 수 있는 문제입니다. 서로 친한 친구끼리 그룹을 만들때, 친구비가 싼 친구가 (유니온-파인드에서)부모 노드가 되도록 합니다. 
- [친구 네트워크](https://www.acmicpc.net/problem/4195)
  - 유니온-파인드만으로도 제한 시간 내에 풀 수 있지만, **해시**까지 사용하면 더 빠르게 풀 수 있는 문제입니다.
- [방 청소](https://www.acmicpc.net/problem/9938) :star::star::star:
- [공항](https://www.acmicpc.net/problem/10775) :star::star::star:
  - 처음에는 이걸 어떻게 유니온-파인드로 풀어? 생각을 하지만, 풀이법을 알고나니 정말 유니온-파인드를 사용하기에 최적의 문제이다. 
- [통신망 분할](https://www.acmicpc.net/problem/17398) :star:
  - 제거가 이루어지는 순서를 거꾸로 이용하면 집합을 묶으면서 풀 수 있는 문제이다. 
- [네트워크 연결](https://www.acmicpc.net/problem/3780) :star::star:
  - **경로압축**의 진수를 보여주는 문제입니다. 네트워크 연결이 진행될 수록 간선이 어떻게 추가되고 이 간선 사이의 거리를 어떻게 압축할 수 있는지를 그려야 되는 문제입니다.



### Heap

- [최대 힙](https://www.acmicpc.net/problem/11279) :star:
  - 힙을 구현할 수 있나 묻는 문제입니다.
- [최소 힙](https://www.acmicpc.net/problem/1927) :star:
  - 힙을 구현할 수 있나 묻는 문제입니다.
- [가운데를 말해요](https://www.acmicpc.net/problem/1655) :star::star::star:
  - 최소 힙과 최대 힙을 사용하여 가운데 값을 추출하는 문제입니다. 이런건 **레퍼런스 문제**로 잘 알아두어야 합니다.



### BST

- [듣보잡](https://www.acmicpc.net/problem/1764)
  - 풀이 방법으로 트라이, STL map, STL set, STL unordered_map, 투 포인터 모두 가능합니다.
- [회사에 있는 사람](https://www.acmicpc.net/problem/7785) :star:
  - 회사에 남아있는 사람을 구하는 문제입니다. 회사에 남아있는 사람의 이름이 문자열을 역 사전순으로 출력해야 하기 때문에,  set을 이용하면 좋은 문제입니다. set은 BST특성상 in-order순회 시 사전순으로, 마찬가지로 pre-order시에는 역 사전순으로 출력되기 때문입니다. (trie로도 풀 수 좋을듯!)



## String Searching Algorithm

### Rabin-Carp Algorithm

- [부분 문자열](https://www.acmicpc.net/problem/16916) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/StringSearching/%5BBOJ_16916%5D%EB%B6%80%EB%B6%84%20%EB%AC%B8%EC%9E%90%EC%97%B4.cpp)
  
  - 라빈카프 알고리즘을 사용하여 부분 문자열을 찾을 수 있다. 진법(base)과 소수 선별에 따라서 해쉬 충돌 횟수가 달라지므로, 적절한 진법과 소수를 선별해야 한다.



### KMP

- [찾기](https://www.acmicpc.net/problem/1786) ​[[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/StringSearching/%5BBOJ_1786%5D%EC%B0%BE%EA%B8%B0.cpp) :star:
  
  - 해당 문자열에서 임의의 패턴이 어느 위치에서 존재하는지 확인하는 문제이다. S문자열에서 P패턴을 찾는 문제임으로 KMP를 사용하면 빠르게 구할 수 있다. 전형적인 KMP 연습문제이다.
  
- [광고](https://www.acmicpc.net/problem/1305) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/StringSearching/%5BBOJ_1305%5D%EA%B4%91%EA%B3%A0.cpp) :star::star: ​
  
  - KMP를 어떻게 적용해야 하나 고민이 되었던 문제이다. 전광판 특징에 따라 문자열이 다시 반복되면 prefix와 suffix가 같아지게 된다. 이 특징을 이용하여 KMP를 적용하면 풀 수 있는 문제이다.
  
- [Cubeditor](https://www.acmicpc.net/problem/1701) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/StringSearching/%5BBOJ_1701%5DCubeditor.cpp) :star::star::star:
  
  - KMP를 사용하지 않았더라면 풀기 막막한 문제이다. 주어진 문자열에서 prefix와 sufix가  같은 것이 있는지 찾아야 한다. 
  
- [순환 순열](https://www.acmicpc.net/problem/12104) :star:

  - 라빈카프를 써서 풀 수 있는 줄 알았는데, 해시 충돌이 날때는 문자열이 같나 검사해줘야 하기 때문에 시간초과가 납니다.  순환 순열의 특징을 잘 생각해서 KMP를 사용하면 풀 수 있는 문제입니다.

- [카멜레온 부분 문자열](https://www.acmicpc.net/problem/13506) :star:

  - prefix와 suffix와 같으면서 부분 문자열이 있는지 확인하는 문제입니다. prefix, suffix가 같은것이 있는지 확인하는 kmp의 fail이 의미하는 바를 활용하면 풀 수 있는 문제입니다.

- [Prefix와 Suffix](https://www.acmicpc.net/problem/13576) :star::star::star:

  - 모르겠다... 백준선생님께 여쭤보자
  
  

### Trie

- [접두사 찾기](https://www.acmicpc.net/problem/14426)
  - 전형적인 Trie문제이다. S문자열 집합에서 M문자열이 접두사로 나타나지는지 확인하는 문제이다.
- [두 수 XOR](https://www.acmicpc.net/problem/13505) :star::star::star:
  - 입력된 숫자를 32길이의 문자열로 생각해서 트라이에 넣어서 풀 수 있는 문제입니다. (주어진 입력은 int형 범위 안이다.)  집한 안의 숫자와 xor했을 때 가장 큰 숫자를 구해기 위해서는 비트가 1일때 0을, 0일때 1을 찾도록 해야 합니다. 
- [문자열 집합](https://www.acmicpc.net/problem/14425) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/StringSearching/%5BBOJ_14425%5D%EB%AC%B8%EC%9E%90%EC%97%B4%20%EC%A7%91%ED%95%A9.cpp)
  - S문자열 집합에 M문자열 집합이 몇 개나 포함되나 확인하는 문제이다. 문제 이름만 다르지 듣보잡이랑 같은 문제이다. Trie를 써서 S문자열 집합에서 M문자열 집합의 문자열들이 존재하는지 확인하면 된다. 
- [전화번호 목록](https://www.acmicpc.net/problem/5052)
  - 한 번호가 다른 번호들의 접두어인지 아닌지를 판별하는 문제입니다. 접두사 판별은 역시 트라이죠
- [휴대폰 자판](https://www.acmicpc.net/problem/5670) :star::star:
  - 트라이 노드에서 자식이 두 개 이상 있으면 타이핑을 할 수 밖에 없다는 점을 이용해서 풀어야 합니다. 어느 문자열이 다른 문자열의 접두사가 되는 경우에도 타이핑을 한 번 더 쳐야 합니다. 재귀 호출을 통해 전체 트라이를 탐색하는 방식으로 해결할 수 있습니다. 어차피 트라이도 트리구조이기 때문입니다.
- [생태학](https://www.acmicpc.net/problem/4358) :star:
  - 트라이 속성을 이용해서 주어진 문자열을 사전순으로 나열하면 되는 문제입니다.
- [Boggle](https://www.acmicpc.net/problem/9202) :star:
- [부분 수열 XOR](https://www.acmicpc.net/problem/13445) :star::star::star:
- [XOR 합](https://www.acmicpc.net/problem/13504) :star::star::star:
  - 같은 숫자를 XOR하면 0이 된다는 특징을 이용하여 푸는 문제입니다. 넘나 참신...

###  

### Aho-Corasick

- [문자열 집합 판별](https://www.acmicpc.net/problem/9250) :star::star:
  - 아호코라식을 적용해보는 문제입니다.
- [돌연변이](https://www.acmicpc.net/problem/10256) :star::star::star:
  - 아호코라식을 적용해보는 문제입니다. 문자열 마커를 세 등분하여 가운데만 뒤집는 것을 구현해야 됩니다.
- [아스키 거리](https://www.acmicpc.net/problem/2809)
  - trie에서 자식노드 탐색을 맵으로 하다니;;;



## Dynamic Programming

- [1로 만들기](https://www.acmicpc.net/problem/1463)
- [2×n 타일링](https://www.acmicpc.net/problem/11726)
- [2×n 타일링 2](https://www.acmicpc.net/problem/11727)
- [1, 2, 3 더하기](https://www.acmicpc.net/problem/9095)
- [1, 2, 3 더하기 3](https://www.acmicpc.net/problem/15988)
- [카드 구매하기](https://www.acmicpc.net/problem/11052)
- [카드 구매하기 2](https://www.acmicpc.net/problem/16194)
- [1, 2, 3 더하기 5](https://www.acmicpc.net/problem/15990)
- [쉬운 계단 수](https://www.acmicpc.net/problem/10844)
- [오르막 수](https://www.acmicpc.net/problem/11057)
- [이친수](https://www.acmicpc.net/problem/2193)
- [스티커](https://www.acmicpc.net/problem/9465)
- [포도주 시식](https://www.acmicpc.net/problem/2156)
- [가장 긴 증가하는 부분 수열](https://www.acmicpc.net/problem/11053)
- [가장 긴 증가하는 부분 수열 4](https://www.acmicpc.net/problem/14002)
- [가장 큰 증가하는 부분 수열](https://www.acmicpc.net/problem/11055)
- [가장 긴 감소하는 부분 수열](https://www.acmicpc.net/problem/11722)
- [가장 긴 바이토닉 부분 수열](https://www.acmicpc.net/problem/11054)
- [연속합](https://www.acmicpc.net/problem/1912)
- [연속합 2](https://www.acmicpc.net/problem/13398)
- [제곱수의 합](https://www.acmicpc.net/problem/1699)
- [합분해](https://www.acmicpc.net/problem/2225)
- [이동하기](https://www.acmicpc.net/problem/11048)
- [점프 점프](https://www.acmicpc.net/problem/11060)
- [퇴사 2](https://www.acmicpc.net/problem/15486)
- [팰린드롬?](https://www.acmicpc.net/problem/10942)
- [1, 2, 3 더하기 4](https://www.acmicpc.net/problem/15989)
- [파일 합치기](https://www.acmicpc.net/problem/11066)
- [평범한 배낭](https://www.acmicpc.net/problem/12865)
- [기타리스트](https://www.acmicpc.net/problem/1495)
- [뮤탈리스크](https://www.acmicpc.net/problem/12869)
- [괄호](https://www.acmicpc.net/problem/10422)
- [동전 1](https://www.acmicpc.net/problem/2293)
- [동전 2](https://www.acmicpc.net/problem/2294)
- [크리보드](https://www.acmicpc.net/problem/11058)
- [점프](https://www.acmicpc.net/problem/1890)
- [행렬 곱셈 순서](https://www.acmicpc.net/problem/11049)
- [1학년](https://www.acmicpc.net/problem/5557)
- [ABC](https://www.acmicpc.net/problem/12969)
- [출근 기록](https://www.acmicpc.net/problem/14238)
- [BOJ 거리](https://www.acmicpc.net/problem/12026)
- [Acka](https://www.acmicpc.net/problem/12996)
- [데스노트](https://www.acmicpc.net/problem/2281)
- [올바른 괄호 문자열](https://www.acmicpc.net/problem/3012)
- [소형기관차](https://www.acmicpc.net/problem/2616)
- [박스 안의 열쇠](https://www.acmicpc.net/problem/1413)
- [팔굽혀펴기](https://www.acmicpc.net/problem/10564)
- [건배](https://www.acmicpc.net/problem/1970)
- [초콜릿 자르기](https://www.acmicpc.net/problem/2163)
- [플레이리스트](https://www.acmicpc.net/problem/12872)
- [N-Rook II](https://www.acmicpc.net/problem/1767)



## Binary Search

- [수 찾기](https://www.acmicpc.net/problem/1920)
  - 이진 탐색을 이용해서 주어진 숫자가 배열에 존재하는 지 찾는 문제입니다. 파이썬을 이용하면 이분 탐색을 직접 짤 필요없이 set에 값이 존재하는지 판별할 수 있습니다. 

- [수 이어 쓰기 2](https://www.acmicpc.net/problem/1790)

- [랜선 자르기](https://www.acmicpc.net/problem/1654)

- [나무 자르기](https://www.acmicpc.net/problem/2805)

- [공유기 설치](https://www.acmicpc.net/problem/2110)

- [중량제한](https://www.acmicpc.net/problem/1939)

- [사다리](https://www.acmicpc.net/problem/2022)

- [선분과 점](https://www.acmicpc.net/problem/11664)

- [기타 레슨](https://www.acmicpc.net/problem/2343)

- [구간 나누기 2](https://www.acmicpc.net/problem/13397)

- [배열에서 이동](https://www.acmicpc.net/problem/1981)

- [K번째 수](https://www.acmicpc.net/problem/1300)

- [놀이 공원](https://www.acmicpc.net/problem/1561)
- [메탈](https://www.acmicpc.net/problem/9460) :star::star:



## Math

- [곱셈](https://www.acmicpc.net/problem/1629)

- [행렬 제곱](https://www.acmicpc.net/problem/10830)

- [피보나치 수](https://www.acmicpc.net/problem/2747)

- [피보나치 수 2](https://www.acmicpc.net/problem/2748)

- [피보나치 수 3](https://www.acmicpc.net/problem/2749)

- [피보나치 수 6](https://www.acmicpc.net/problem/11444)

- [이항 계수 1](https://www.acmicpc.net/problem/11050)

- [이항 계수 2](https://www.acmicpc.net/problem/11051)

- [소수의 배수](https://www.acmicpc.net/problem/17436)

- [제곱 ㄴㄴ 수](https://www.acmicpc.net/problem/1016)

- [제곱 ㄴㄴ](https://www.acmicpc.net/problem/1557)

- [이항 계수 4](https://www.acmicpc.net/problem/11402)

- [이항 계수 5](https://www.acmicpc.net/problem/11439)

- [GCD(n, k) = 1](https://www.acmicpc.net/problem/11689)

- [이항 계수 3](https://www.acmicpc.net/problem/11401)

  

## Geometric Algorithm

- [CCW](https://www.acmicpc.net/problem/11758)

- [다각형의 면적](https://www.acmicpc.net/problem/2166)

- [선분 교차 1](https://www.acmicpc.net/problem/17386)

- [선분 교차 2](https://www.acmicpc.net/problem/17387)

- [지민이의 테러](https://www.acmicpc.net/problem/1688)

- [볼록 껍질](https://www.acmicpc.net/problem/1708)

- [가장 가까운 두 점](https://www.acmicpc.net/problem/2261)

- [최대 직사각형](https://www.acmicpc.net/problem/11873)

- [겹치는 선분](https://www.acmicpc.net/problem/1689)

- [선 긋기](https://www.acmicpc.net/problem/2170)



## Etc

  - [LCD Test](https://www.acmicpc.net/problem/2290) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/Simulation/%5BBOJ_2290%5DLCD%20Test.cpp)
    
      - LCD에 출력되는 숫자의 규칙을 파악하면 풀 수 있는 문제이다.
    
  - [잃어버린 괄호](https://www.acmicpc.net/problem/1541) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/Simulation/%5BBOJ_1541%5D%EC%9E%83%EC%96%B4%EB%B2%84%EB%A6%B0%20%EA%B4%84%ED%98%B8.cpp)
  
    - 주어진 연산 문자열에 괄호를 추가하여 최솟값을 추출하는 문제이다. 연산부호가 +,-밖에 없으므로 탐욕법을 통해 풀 수 있다.
  
  - [시험감독](https://www.acmicpc.net/problem/13458) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/Simulation/%5BBOJ_13458%5D%EC%8B%9C%ED%97%98%EA%B0%90%EB%8F%85.cpp)

      - 각 반마다 돌아다니면서 필요한 최소 감독관을 구하는 문제이다. 

  - [팀나누기](https://www.acmicpc.net/problem/13866) [[cpp]](https://github.com/SwimmingLee/Algorithm/blob/master/Simulation/%5BBOJ_13866%5D%ED%8C%80%EB%82%98%EB%88%84%EA%B8%B0.cpp)
  
    - 4명이 둘둘 팀을 나누는 데 능력치를 가능하면 골고루 분배하도록 하는 문제이다. 
    
      

## Reference Code

### Data Instruction

- Union-Find(Disjoint-set)

- BST

- Heap

- Hash

  
### String

- RanbinCarp Algorithm

- KMP

- BitMask

- Trie

- Aho-corasick

  

### Sort

- Bubble Sort

- Quick Sort

- Merge Sort

- Insertion Sort

- Selection Sort

- Heap Sort

- Counting Sort

### Math

- Sieve of Eratosthenes
- GCD and LCM