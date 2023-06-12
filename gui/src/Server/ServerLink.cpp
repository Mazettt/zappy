#include "../../includes/Server/ServerLink.hpp"
#include "../../includes/Game.hpp"

using namespace ZappyGui;

ServerLink::ServerLink(Game &game): _game(game) {
    _init();
}

ServerLink::ServerLink(Game &game, const std::string &ip, uint16_t port): _game(game), _socket(ip, port) {
    _init();
    connect(ip, port);
}

ServerLink::ServerLink(ServerLink &&other): _game(other._game), _socket(std::move(other._socket)) {}

ServerLink::~ServerLink() {}

ServerLink &ServerLink::operator=(ServerLink &&other)
{
    _socket = std::move(other._socket);
    return *this;
}

void ServerLink::connect(const std::string &ip, uint16_t port)
{
    _socket.connect(ip, port);
    _socket << "GRAPHIC\n";
}

void ServerLink::askMapSize()
{
    _socket << "msz\n";
}

void ServerLink::askTileContent(int x, int y)
{
    _socket << "bct " + std::to_string(x) + " " + std::to_string(y) + "\n";
}

void ServerLink::askMapContent()
{
    _socket << "mct\n";
}

void ServerLink::askTeamNames()
{
    _socket << "tna\n";
}

void ServerLink::askPlayerPosition(int id)
{
    _socket << "ppo " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerLevel(int id)
{
    _socket << "plv " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerInventory(int id)
{
    _socket << "pin " + std::to_string(id) + "\n";
}

void ServerLink::askTimeUnit()
{
    _socket << "sgt\n";
}

void ServerLink::modifyTimeUnit(int timeUnit)
{
    _socket << "sst " + std::to_string(timeUnit) + "\n";
}

void ServerLink::update()
{
    std::string buff;
    if (!_socket.tryRead(buff))
        return;
    buff = buff.substr(0, buff.size() - 1);
    std::vector<std::string> commands = split(buff, '\n');
    for (const auto &command : commands) {
        std::cout << "command: " << command << std::endl;
        if (_responseFunctions.find(command.substr(0, 3)) != _responseFunctions.end())
            (this->*_responseFunctions[command.substr(0, 3)])(command);
    }
}

void ServerLink::_init()
{
    _responseFunctions["msz"] = &ServerLink::_msz;
    _responseFunctions["bct"] = &ServerLink::_bct;
    _responseFunctions["tna"] = &ServerLink::_tna;
    _responseFunctions["pnw"] = &ServerLink::_pnw;
    _responseFunctions["ppo"] = &ServerLink::_ppo;
    _responseFunctions["plv"] = &ServerLink::_plv;
    _responseFunctions["pin"] = &ServerLink::_pin;
    _responseFunctions["pex"] = &ServerLink::_pex;
    _responseFunctions["pbc"] = &ServerLink::_pbc;
    _responseFunctions["pic"] = &ServerLink::_pic;
    _responseFunctions["pie"] = &ServerLink::_pie;
    _responseFunctions["pfk"] = &ServerLink::_pfk;
    _responseFunctions["pdr"] = &ServerLink::_pdr;
    _responseFunctions["pgt"] = &ServerLink::_pgt;
    _responseFunctions["pdi"] = &ServerLink::_pdi;
    _responseFunctions["enw"] = &ServerLink::_enw;
    _responseFunctions["ebo"] = &ServerLink::_ebo;
    _responseFunctions["edi"] = &ServerLink::_edi;
    _responseFunctions["sgt"] = &ServerLink::_sgt;
    _responseFunctions["sst"] = &ServerLink::_sst;
    _responseFunctions["seg"] = &ServerLink::_seg;
    _responseFunctions["smg"] = &ServerLink::_smg;
    _responseFunctions["suc"] = &ServerLink::_suc;
    _responseFunctions["sbp"] = &ServerLink::_sbp;
}

void ServerLink::_msz(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int x, y;

    iss >> tmp >> x >> y;
    this->_game._map.createMap(x, y);
}

void ServerLink::_bct(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    float x, z;
    int food, linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> tmp >> x >> z >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

    std::cout << "add resource for tile x (" << x << ") z(" << z << ") food(" << food << ") linemate(" << linemate << ") deraumere(" << deraumere << ") sibur(" << sibur << ") mendiane(" << mendiane << ") phiras(" << phiras << ") thystame(" << thystame << ")" << std::endl;

    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::BURGER, food);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::LINEMATE, linemate);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::DERAUMERE, deraumere);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::SIBUR, sibur);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::MENDIANE, mendiane);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::PHIRAS, phiras);
    this->_game._map.addResourceForTile({ (float)x, (float)z }, IResource::resourceType::THYSTAME, thystame);

}

void ServerLink::_tna(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp, teamName;

    iss >> tmp >> teamName;
    std::cout << "Team name: " << teamName << std::endl;
}

void ServerLink::_pnw(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, level;
    float x, z, rotationAngle;
    std::string teamName;

    iss >> tmp >> id >> x >> z >> rotationAngle >> level >> teamName; // TO CHECK orientation
    PlayerArguments playerArgs = PlayerArguments(id, teamName, { x, 0.0, z }, {0.0f, 1.0f, 0.0f}, rotationAngle, {0.6f, 0.6f, 0.6f}, 0, Player::animationPlayerType::PLAYER_NOTHING);
    this->_game._map.addPlayerForTile(playerArgs);
}

void ServerLink::_ppo(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, orientation;
    float x, z;

    iss >> tmp >> id >> x >> z >> orientation;
    this->_game._map.movePlayer(id, x, z, (ZappyGui::Player::orientationAxis) orientation); // TO CHECK orientation
}

void ServerLink::_plv(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, level;

    iss >> tmp >> id >> level;
    this->_game._map.setPlayerLevel(id, level);
}

void ServerLink::_pin(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> tmp >> id >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    std::cout << "Player inventory: " << id << " " << x << " " << y << " -> " << food << " " << linemate << " " << deraumere << " " << sibur << " " << mendiane << " " << phiras << " " << thystame << std::endl;
}

void ServerLink::_pex(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    std::cout << "Player explosion: " << id << std::endl;
}

void ServerLink::_pbc(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;
    std::string message;

    iss >> tmp >> id >> message;
    std::cout << "Player broadcast: " << id << " " << message << std::endl;
}

void ServerLink::_pic(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int level;
    float x, z;
    std::vector<int> ids;

    iss >> tmp >> x >> z >> level;
    for (int id; iss >> id;)
        ids.push_back(id);
    this->_game._map.StartPlayersLeveling(ids, level, x, z);
    std::cout << std::endl;
}

void ServerLink::_pie(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int result;
    float x, z;

    iss >> tmp >> x >> z >> result;
    this->_game._map.EndPlayersLeveling(x, z, result);
}

void ServerLink::_pfk(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    std::cout << "Player fork: " << id << std::endl;
}

void ServerLink::_pdr(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, resource;

    iss >> tmp >> id >> resource;
    this->_game._map.dropResource(id, (ZappyGui::IResource::resourceType) resource); // TO CHECK if resourceType work correctly
}

void ServerLink::_pgt(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, resource;

    iss >> tmp >> id >> resource;
    this->_game._map.collectResource(id, (ZappyGui::IResource::resourceType) resource); // TO CHECK if resourceType work correctly
}

void ServerLink::_pdi(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    this->_game._map.deadPlayer(id);
}

void ServerLink::_enw(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId, playerId, x, y;

    iss >> tmp >> eggId >> playerId >> x >> y;
    std::cout << "Egg new: " << eggId << " " << playerId << " " << x << " " << y << std::endl;
}

void ServerLink::_ebo(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId;

    iss >> tmp >> eggId;
    std::cout << "Egg born: " << eggId << std::endl;
}

void ServerLink::_edi(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId;

    iss >> tmp >> eggId;
    std::cout << "Egg death: " << eggId << std::endl;
}

void ServerLink::_sgt(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int time;

    iss >> tmp >> time;
    std::cout << "Time unit: " << time << std::endl;
}

void ServerLink::_sst(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int time;

    iss >> tmp >> time;
    std::cout << "Time unit set: " << time << std::endl;
}

void ServerLink::_seg(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    std::string teamName;

    iss >> tmp >> teamName;
    std::cout << "End of game: " << teamName << std::endl;
}

void ServerLink::_smg(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    std::string message;

    iss >> tmp >> message;
    std::cout << "Server message: " << message << std::endl;
}

void ServerLink::_suc(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Unknown command" << std::endl;
}

void ServerLink::_sbp(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Bad parameter" << std::endl;
}
