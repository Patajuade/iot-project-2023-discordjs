import './App.css';
const onSubmit = () => {
    fetch("https://connected-dice-api.azurewebsites.net/config", {
        "method": "POST",
        "headers": {
            "Content-Type": "application/json"
        },
        "body": JSON.stringify({
            "newValue": document.getElementById("dice").value
        })
    })
}
function App() {

  return (
      <body>
      <h1>Dice Configuration</h1>
      <p>Manage your configuration</p>
      <div >
          <label htmlFor="dice">Dice max value:</label>
          <input type="number" id="dice" name="dice" min="1" max="20" required/>
          <button type="submit" onClick={onSubmit}>Submit</button>
      </div>
      </body>
  );
}

export default App;
