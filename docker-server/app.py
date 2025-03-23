from flask import Flask, request

app = Flask(__name__)

# Store incoming messages
messages = []

@app.route('/', methods=['GET', 'POST'])
def log_messages():
    if request.method == 'POST':
        message = request.get_data(as_text=True)  # Get raw message body
        messages.append(message)
    
    # Show received messages
    return "<h1>Received Messages:</h1>" + "<br>".join(messages)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
