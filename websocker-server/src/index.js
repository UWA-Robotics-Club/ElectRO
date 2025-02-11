const express = require("express");
const WebSocket = require("ws");

const app = express();
const port = 8080;

// Serve the HTML dashboard
app.use(express.static("public"));

const server = app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});

// Create a WebSocket server
const wss = new WebSocket.Server({ server });

wss.on("connection", (ws) => {
  console.log("Client connected");

  ws.on("message", (message) => {
    // Convert the Buffer to a string
    const messageStr = message.toString();

    try {
      // Parse the JSON string into an object
      const data = JSON.parse(messageStr);

      // // Log the parsed data
      // console.log("Parsed Data:", data);

      // Broadcast to other clients (if needed)
      wss.clients.forEach((client) => {
        if (client.readyState === WebSocket.OPEN) {
          client.send(JSON.stringify(data));
        }
      });
    } catch (err) {
      console.error("Failed to parse JSON:", err.message);
    }
  });

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});
