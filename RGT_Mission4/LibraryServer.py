from flask import Flask, request, jsonify 

app = Flask(__name__)

users = []   # 사용자 저장
books = []   # 책 저장
loans = []   # 대출 목록

# 1. 회원가입
@app.route("/auth/signup", methods=["POST"])
def signup():
    data = request.json
    users.append(data)
    return jsonify({"msg": "Signup success", "user": data}), 201

# 2. 로그인
@app.route("/auth/login", methods=["POST"])
def login():
    data = request.json
    for u in users:
        if u["username"] == data["username"] and u["password"] == data["password"]:
            return jsonify({"access_token": "dummy_token"}), 200
    return jsonify({"error": "invalid credentials"}), 401

# 3. 책 등록
@app.route("/books", methods=["POST"])
def add_book():
    data = request.json
    books.append(data)
    return jsonify({"msg": "Book added", "book": data}), 201

# 4. 책 검색
@app.route("/books", methods=["GET"])
def search_books():
    category = request.args.get("category")
    available = request.args.get("available")
    result = books
    if category:
        result = [b for b in result if b["category"] == category]
    return jsonify(result), 200

# 5. 대출 등록
@app.route("/loans", methods=["POST"])
def borrow_book():
    data = request.json
    loans.append(data)
    return jsonify({"msg": "Book borrowed", "loan": data}), 201

# 6. 내 대출 조회
@app.route("/users/me/loans", methods=["GET"])
def my_loans():
    return jsonify(loans), 200

if __name__ == "__main__":
    app.run(debug=True, port=8000)