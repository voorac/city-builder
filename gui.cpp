#include "gui.hpp"


GuiStyle::GuiStyle()
{}

GuiStyle::GuiStyle(sf::Font font, float borderSize,
    sf::Color bodyCol,
    sf::Color bodyHighlightCol,
    sf::Color borderCol,
    sf::Color borderHighlightCol,
    sf::Color textCol,
    sf::Color textHighlightCol)
    : font(font), borderSize(borderSize), bodyCol(bodyCol), bodyHighlightCol(bodyHighlightCol),
    borderCol(borderCol), borderHighlightCol(borderHighlightCol), textCol(textCol),
    textHighlightCol(textHighlightCol)
{}

GuiEntry::GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
    : message(message), shape(shape), text(text)
{}


Gui::Gui(sf::Vector2f dimensions, int padding, bool horizontal,
    GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries)
    : visible(false), horizontal(horizontal), style(style), dimensions(dimensions),
    padding(padding)
{
    sf::RectangleShape shape;
    shape.setSize(dimensions);
    shape.setFillColor(style.bodyCol);
    shape.setOutlineThickness(-style.borderSize);
    shape.setOutlineColor(style.borderCol);

    for (auto entry : entries)
    {
        sf::Text text;
        text.setString(entry.first);
        text.setFont(style.font);
        text.setColor(style.textCol);
        text.setCharacterSize(dimensions.y - style.borderSize - padding);

        this->entries.push_back(GuiEntry(entry.second, shape, text));
    }
}

sf::Vector2f Gui::getSize()
{
    return sf::Vector2f(this->dimensions.x, this->dimensions.y * this->entries.size());
}

int Gui::getEntry(const sf::Vector2f mousePos)
{
    if (entries.size() == 0) return -1;
    if (!this->visible) return -1;

    for (int i = 0; i < this->entries.size(); i++)
    {
        sf::Vector2f point = mousePos;
        point += this->entries[i].shape.getOrigin();
        point -= this->entries[i].shape.getPosition();

        if (point.x < 0 || point.x > this->entries[i].shape.getScale().x * this->dimensions.x)
            continue;
        if (point.y < 0 || point.y > this->entries[i].shape.getScale().y * this->dimensions.y)
            continue;
        return i;
    }
    return -1;
}

void Gui::setEntryText(int entry, std::string text)
{
    if (entry >= entries.size() || entry < 0)
        return;
    entries[entry].text.setString(text);
}

void Gui::setDimensions(sf::Vector2f dimensions)
{
    this->dimensions = dimensions;

    for (auto& entry : entries)
    {
        entry.shape.setSize(dimensions);
        entry.text.setCharacterSize(dimensions.y - style.borderSize - padding);
    }
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!visible)
        return;

    for (auto entry : this->entries)
    {
        target.draw(entry.shape);
        target.draw(entry.text);
    }
}

void Gui::show()
{
    sf::Vector2f offset(0.0f, 0.0f);
    this->visible = true;

    for (auto& entry : this->entries)
    {
        sf::Vector2f origin = this->getOrigin();
        origin -= offset;
        entry.shape.setOrigin(origin);
        entry.text.setOrigin(origin);

        entry.shape.setPosition(this->getPosition());
        entry.text.setPosition(this->getPosition());

        if (this->horizontal)
            offset.x += this->dimensions.x;
        else
            offset.y += this->dimensions.y;
    }
}


void Gui::hide()
{
    this->visible = false;
}

void Gui::highlight(const int entry)
{
    for (int i = 0; i < entries.size(); i++)
    {
        if (i == entry)
        {
            entries[i].shape.setFillColor(style.bodyHighlightCol);
            entries[i].shape.setOutlineColor(style.borderHighlightCol);
            entries[i].text.setColor(style.textHighlightCol);
        }
        else
        {
            entries[i].shape.setFillColor(style.bodyCol);
            entries[i].shape.setOutlineColor(style.borderCol);
            entries[i].text.setColor(style.textCol);
        }
    }
}

std::string Gui::activate(const int entry)
{
    if (entry == -1) return "null";
    return entries[entry].message;
}

std::string Gui::activate(sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    return this->activate(entry);
}
