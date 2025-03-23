from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST', 'PUT', 'DELETE'])
def log_request():
    print(f"Incoming request: {request.method} {request.url}")
    print(f"Headers: {request.headers}")
    print(f"Body: {request.data.decode('utf-8')}")
    return '', 200  

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
