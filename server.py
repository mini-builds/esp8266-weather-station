from flask import Flask
from flask import request

app = Flask(__name__)

# A simple server that prints the body of a POST request to '/'

@app.route("/", methods=['POST'])
def data():
    print(request.data)

    return "Added data"

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80)
