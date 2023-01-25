
//main
// node main.js -> to run
// ctrl + C -> to stop

// Require the necessary discord.js classes
const fs = require('node:fs'); //fs is Node's native file sustem module
const { Client, Collection ,Intents } = require('discord.js');
const { token } = require('./config.json');
const {message,getAttachement,getThumbnail} = require('./commands/eventDecoy');

//REST API part
const express = require("express");
const { json } = require('express/lib/response');
const app = express();
const port = 80;
app.use(express.json());
app.use(express.urlencoded({extended:true}));
app.listen(port,()=>{
	console.log("Express API is ready");
});

//localhost:8080/roll
//comportement quand le client fait get
app.get("/roll",(req,res)=>{
	const {result} = req.query; //récupère result dans l'URL : localhost:8080/roll?result=5
	if(result>0 && result<=20){
		const file = getAttachement(result);
		const thumbnail = getThumbnail();
	
		const chan = client.channels.cache.find(c=>c.name==="général");
		chan.send({ embeds: [message("La main", "https://cdn.mycrazystuff.com/10416/mini-main-pour-doigt.jpg")],files: [file,thumbnail] });
		return res.status(200).json({
			message:result
		});
	}
	return res.status(402).json({
		message:"Action non autorisée :("
	});
});


// Create a new client instance
const client = new Client({ intents: [Intents.FLAGS.GUILDS] });
client.commands = new Collection(); //We recommend attaching a .commands property to your client instance so that you can access your commands in other files
const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js')); // fs.readdirSync() method will return an array of all the file names in a directory

for (const file of commandFiles) {
	const command = require(`./commands/${file}`);
	// Set a new item in the Collection
	// With the key as the command name and the value as the exported module
	client.commands.set(command.data.name, command);
}

// When the client is ready, run this code (only once)
client.once('ready', () => {
	console.log('Discord bot is ready!');
});

//replying to commands
client.on('interactionCreate', async interaction => {
	if (!interaction.isCommand()) return; //check if an interaction is a command

	const command = client.commands.get(interaction.commandName);

	if (!command) return;

	try {
		await command.execute(interaction);
	} catch (error) {
		console.error(error);
		await interaction.reply({ content: 'There was an error while executing this command!', ephemeral: true });
	}
  
});

// Login to Discord with your client's token
client.login(token);



