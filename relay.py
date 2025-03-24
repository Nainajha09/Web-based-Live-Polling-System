from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

votes = {"A": 0, "B": 0, "C": 0}

@app.route("/")
def home():
    return render_template("index.html", votes=votes)

@app.route("/update_votes", methods=["POST"])
def update_votes():
    global votes
    data = request.json
    votes = data
    socketio.emit("vote_update", votes)
    return jsonify({"status": "updated", "votes": votes})

if __name__ == "__main__":
    socketio.run(app, debug=True, host="0.0.0.0", port=5000)
