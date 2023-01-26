import './App.css';

function App() {
  return (
      <body>
      <h1>Dice Configuration</h1>
      <p>Manage your configuration</p>
      <form action="/api/dice" method="post">
          <label htmlFor="dice">Dice max value:</label>
          <input type="number" id="dice" name="dice" min="1" max="99" required/>
          <input type="submit" value="Submit"/>
      </form>
      </body>
  );
}

export default App;
