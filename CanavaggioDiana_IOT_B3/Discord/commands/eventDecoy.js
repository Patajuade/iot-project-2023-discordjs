
//trying to make an embed message
const { MessageEmbed } = require('discord.js');
const { MessageAttachment } = require('discord.js');
const { SlashCommandBuilder } = require('@discordjs/builders');
const { Guild } = require("discord.js");

//random generator to simulate the future dice
function getRandomArbitrary(min, max) {
    result = Math.random() * (max - min) + min;
    return Math.ceil(result);
  }

  function getAttachement(randomNumber){
    return new MessageAttachment(`./local-resources/${randomNumber}.png`, `result.png`);
  }

  function getThumbnail(){
      return new MessageAttachment(`./local-resources/thumbnail.png`, `thumbnail.png`);
  }

const message = (userInteractingName, userInteractingAvatar)=>new MessageEmbed()
    .setColor('#3c020c')
    .setTitle(userInteractingName + ' a secoué le dé !')
    .setURL('https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley')
    .setAuthor({ name: userInteractingName, iconURL: userInteractingAvatar, url: 'https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley' })
    .setDescription('Quelle souplesse dans le poignet...')
    .setThumbnail('attachment://thumbnail.png')
    .addField('___________________', 'Resultat : ', true)
    .setImage('attachment://result.png')
    .setTimestamp()

module.exports = {
    getAttachement,
    getThumbnail,
    message,
    data: new SlashCommandBuilder()
        .setName('rand')
        .setDescription('Does its job for once'),

    async execute(interaction) {
        //c'est mieux de mettre dans des var
        const randomNumber = getRandomArbitrary(1,20);
        const file = getAttachement(randomNumber);
        const thumbnail = getThumbnail();

        //channel.send({ embeds: [exampleEmbed] });
        await interaction.reply({ embeds: [message(interaction.user.tag, interaction.user.displayAvatarURL())],files: [file,thumbnail] });
        //const guild = new Guild(interaction.guild.id).channels;
        //console.log(guild);
    }
}