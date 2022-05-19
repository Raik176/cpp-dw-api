#include "discord.h"

int main() {
    discord::Webhook w("guild_id","webhook_id");
    std::list<discord::Embed> embeds;
    discord::Embed e;
    e.setAuthor("Author","https://cdn.discordapp.com/avatars/584719109972033546/70f301b8c0138af325aafe886b6606d7.png?size=256");
    e.setColor(0x064121);
    e.setDescription("Description");
    e.setFooter("Footer");
    e.setImage("https://cdn.discordapp.com/avatars/584719109972033546/70f301b8c0138af325aafe886b6606d7.png?size=256");
    e.setProvider("https://cdn.discordapp.com/avatars/584719109972033546/70f301b8c0138af325aafe886b6606d7.png?size=256","Provider");
    e.setThumbnail("https://cdn.discordapp.com/avatars/584719109972033546/70f301b8c0138af325aafe886b6606d7.png?size=256");
    e.setTitle("Title");
    e.setURL("https://cdn.discordapp.com/avatars/584719109972033546/70f301b8c0138af325aafe886b6606d7.png?size=256");
    e.addField("This is a field","not inline!");
    e.addField("This is a field","not inline!");
    e.addField("This is a field","but inline!",true);
    e.addField("This is a field","but inline!",true);
    embeds.assign(1,e);
    std::cout << w.sendMessage("Embed:",embeds) << std::endl;
}