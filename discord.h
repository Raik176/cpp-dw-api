#include <iostream>
#include <list>
#include <cpr/api.h>
#include <string>

using namespace std;
using namespace cpr;

namespace discord {
    class Embed {
        string title = "";
        string description = "";
        string url = "";
        string footer;
        string image;
        string thumbnail;
        string video;
        string provider;
        string author;
        vector<string> fields;
        int color = 0x000000;
        public:
            Embed* setTitle(string title) {
                this->title = title;
                return this;
            }

            Embed* setDescription(string description) {
                this->description = description;
                return this;
            }

            Embed* setURL(string url) {
                this->url = url;
                return this;
            }
            Embed* setColor(int hex) {
                this->color = hex;
                return this;
            }

            Embed* setFooter(string text) {
                this->footer.append("\"text\":\"").append(text).append("\"");
                return this;
            }
            Embed* setFooter(string text, string icon_url) {
                this->footer.append("\"text\":\"").append(text).append("\",\"icon_url\":\"").append(icon_url).append("\"");
                return this;
            }

            Embed* setImage(string url) {
                this->image.append("\"url\":\"").append(url).append("\"");
                return this;
            }
            Embed* setImage(string url, int width, int height) {
                this->image.append("\"url\":\"").append(url).append("\",\"height\":").append(to_string(height)).append(",\"width\":").append(to_string(width));
                return this;
            }

            Embed* setThumbnail(string url) {
                this->thumbnail.append("\"url\":\"").append(url).append("\"");
                return this;
            }
            Embed* setThumbnail(string url, int width, int height) {
                this->thumbnail.append("\"url\":\"").append(url).append("\",\"height\":").append(to_string(height)).append(",\"width\":").append(to_string(width));
                return this;
            }
            
            Embed* setVideo(string url) {
                this->video.append("\"url\":\"").append(url).append("\"");
                return this;
            }
            Embed* setVideo(string url, int width, int height) {
                this->video.append("\"url\":\"").append(url).append("\",\"height\":").append(to_string(height)).append(",\"width\":").append(to_string(width));
                return this;
            }

            Embed* setProvider(string url) {
                this->provider.append("\"url\":\"").append(url).append("\"");
                return this;
            }
            Embed* setProvider(string url, string name) {
                this->provider.append("\"url\":\"").append(url).append("\",\"name\":\"").append(name).append("\"");
                return this;
            }

            Embed* setAuthor(string name) {
                this->author.append("\"name\":\"").append(name).append("\"");
                return this;
            }
            Embed* setAuthor(string name, string url) {
                this->author.append("\"name\":\"").append(name).append("\",\"url\":\"").append(url).append("\"");
                return this;
            }
            Embed* setAuthor(string name, string url, string icon_url) {
                this->author.append("\"name\":\"").append(name).append("\",\"url\":\"").append(url).append("\",\"icon_url\":\"").append(icon_url).append("\"");
                return this;
            }

            Embed* addField(string title, string value) {
                addField(title,value,false);
                return this;
            }

            Embed* addField(string title, string value, bool inl) {
                string field = "{\"name\":\"";
                field.append(title).append("\",\"value\":\"").append(value).append("\",\"inline\":").append(inl ? "true" : "false").append("}");
                this->fields.push_back(field);
                return this;
            }

            string getJSON() {
                string s = "{";
                string fls;
                for(int i=0;i<fields.size();i++) {
                    string field = fields[i];
                    if (i != (fields.size()-1)) {
                        field.append(",");
                    }
                    fls.append(field);
                }
                s.append("\"title\":\"").append(title).append("\",\"type\":\"rich\",\"description\":\"").append(description).append("\",\"color\":").append(to_string(color)).append(",\"url\":\"").append(url).append("\",\"footer\":{").append(footer).append("},\"image\":{").append(image).append("},\"thumbnail\":{").append(thumbnail).append("},\"video\":{").append(video).append("},\"provider\":{").append(provider).append("},\"author\":{").append(author).append("},\"fields\":[").append(fls).append("]}");
                cout << s << endl;
                return s;
            }
    };
    class Webhook {
        class WebhookInfo {
            public:
                WebhookInfo* setUsername(string name) {

                    return this;
                }
                WebhookInfo* setAvatar(string url) {

                    return this;
                }
        };
        private:
            string url;
        public:
            Webhook(string gid, string wid) {
                string url = "https://discord.com/api/webhooks/";
                url.append(gid).append("/").append(wid);
                this->url = url;
            }
            string sendMessage(string message) {
                return sendMessage(message, list<Embed>());
            }
            string sendMessage(string message, list<discord::Embed> embeds) {
                string json = "{\"content\":\"";
                json.append(message).append("\"");
                if (embeds.size() != 0) {
                    json.append(",\"embeds\":[");
                    for (int i=0;i<embeds.size();i++) {
                        json.append(next(embeds.begin(),i)->getJSON());
                    }
                    json.append("]");
                }
                json.append("}");
                Response res = Post(Url{url}, Body{ json }, Header{ {"Content-Type","application/json"} });
                return res.text;
            }
    };
}
