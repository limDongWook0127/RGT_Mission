## RGT_Misson1,2,3 (LogFileManager, CircularBuffer, ParallelProcessor)

### 설치 환경 정보
- **개발 환경**       : Visual Studio Code  
- **운영체제(OS)**    : Windows 10  
- **컴파일러**        : g++ (MinGW-w64) 15.2.0  
- **언어**            : C++17  
- **빌드 방법**       : VS Code [Ctrl + Shift + B] (tasks.json 자동 빌드)  
- **실행파일**        : main.exe
- **실행 방법**       : cmd에서 실행파일 있는 디렉토리로 이동 후 main.exe 명령어 입력    
- **사용 라이브러리** : 표준 라이브러리(STL)만 사용  


## RGT_Misson4 (LibraryServer)

### 설치 환경 정보
- **개발 환경**       : Visual Studio Code  
- **운영체제(OS)**    : Windows 10  
- **언어**            : Python  
- **사용 프레임워크** : Flask 3.1.2  
- **사용 라이브러리** : requests 2.31.0  
- **실행 방법**       : cmd 또는 VS Code 터미널에서 아래 명령어 실행  
- **서버 실행**       : 파일설치경로\LibraryServer.py  
- **클라이언트 실행** : 파일설치경로\Test_client.py  
- **포트 번호**       : 기본 포트 (http://127.0.0.1:8000)  
- **추가 의존성 설치**: pip install flask requests  

---

## RGT_Mission1 (LogFileManager) 파일 구성 및 역할

**LogFileManager.h** :  LogFileManager 클래스 선언부. OpenLogFile, WriteLog, ReadLogs, CloseLogFile 등의 method 정의와 멤버 변수 선언.  

**LogFileManager.cpp** : LogFileManager 클래스의 구현부. OpenLogFile, WriteLog, ReadLogs, CloseLogFile 등의 실제 동작을 수행.  

**main.cpp** :  LogFileManager 클래스를 테스트. LogFileManager 객체를 생성하고, 로그 파일을 열고 쓰고 읽는 동작을 테스트함.  

**(생성파일)** error.log, debug.log, info.log : 프로그램 실행 시 생성되는 로그 출력 파일.  

---

## RGT_Mission2 (CircularBuffer) 파일 구성 및 역할

**CircularBuffer.h** : 템플릿 기반 원형 버퍼 클래스의 정의. 내부의 std::vector<T>를 사용하여 데이터를 순환 저장하며, push_back, pop_front, size, capacity 등의 기본 메서드와 STL 호환 Iterator를 구현.  

**main.cpp** : CircularBuffer 클래스를 테스트. 버퍼에 데이터를 추가하고 제거하며, 커스텀 반복자를 통해 순회하고 결과를 출력. 또한 std::accumulate, std::max_element 등 STL 알고리즘과의 호환성을 검증.  

---

## RGT_Mission3 (ParallelProcessor) 파일 구성 및 역할

**ParallelProcessor.h** : 템플릿 기반 병렬 처리 클래스 정의. 내부에서 std::thread, std::future, std::async를 이용해 입력 데이터를 여러 청크로 나누어 병렬로 처리할 수 있도록 구현되어 있음.  

**main.cpp** : ParallelProcessor 클래스를 테스트. 1,000,000개의 픽셀 데이터를 초기화하고, parallel_map()으로 병렬 연산을 수행한 뒤, 동일 로직을 for문으로 순차 처리하여 실행 시간을 비교. 픽셀 데이터를 문자열과 제곱값으로 변환하는 테스트를 포함함.  

---

## RGT_Mission4 (LibraryServer) 파일 구성 및 역할

**LibraryServer.py** : Flask 기반 REST API 서버. 회원가입, 로그인, 책 등록, 책 삭제, 검색, 대출의 엔드포인트를 구현함. 내부적으로 users, books, loans 리스트를 통해 데이터를 메모리 상에 관리. 간단한 토큰(dummy_token)으로 인증을 흉내냄.  

**client_test.py** : Python requests 라이브러리를 이용해 서버에 실제 HTTP 요청을 보내는 클라이언트 스크립트. 회원가입, 로그인, 책 등록, 검색, 대출 요청을 순서대로 수행하며 서버 응답(JSON)을 콘솔에 출력함.  

---

## 링크

**상세보기 링크:** [여기를 클릭하세요](https://www.notion.so/RGT-29246a68a94980828ccec9edeffe272f)
