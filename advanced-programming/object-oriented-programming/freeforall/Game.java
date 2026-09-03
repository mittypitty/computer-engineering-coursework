public class Game {
    private Team[] teams;
    private Player[] players;
    int length = 0;
    public Game(Team t1, Team t2) {
        this.teams = new Team[2];
        teams[0] = t1;
        teams[1] = t2;
        addTeamToGame(t1);
        addTeamToGame(t2);
        }

    public void addTeamToGame(Team team){
        this.players =new Player[team.getPlayers().length + length];

        for(int i = 0 ; i < players.length ; i++){
            players[i] = team.getPlayers()[i];
        }
        length += team.getPlayers().length;
    }

    public void score(Player player){
        if(player.getTeam() != null) {
            player.setPoints(player.getPoints() + 1);
            player.getTeam().setScore(player.getTeam().getScore() + 1);
        }  
    }
    public String getScoreBoard(){
        //rank.team name:team score
        for(int i = 0 ; i < teams.length ; i++) {
            for(int j = i + 1 ; j < teams.length ; j++) {
                if(teams[i].getScore() < teams[j].getScore()) {
                    Team tHelp = teams[i];
                    teams[i] = teams[j];
                    teams[j] = tHelp;
                }
            }
        }
        String status = "";
        for(int i = 0 ; i <teams.length ; i++) {
            status += (i + 1) + "." + teams[i].getName() + ":" + teams[i].getScore();
            if(i + 1 != teams.length) {
                status += "\n";
            }
        }
        return status;
    }

    public String topPlayersOnGame(){
        //{player team} {player number} {player name} {player point}
        for(int i = 0 ; i < players.length ; i++) {
            for(int j = i + 1 ; j < players.length ; j++) {
                if(players[i].getPoints() < players[j].getPoints()) {
                    Player pHelp = players[i];
                    players[i] = players[j];
                    players[j] = pHelp;
                }
            }
        }
        String status = "";
        for(int i = 0 ; i < 2 ; i++) {
            if(players[i].getTeam() != null) {
                status += players[i].getTeam() + " " + players[i].getNumber() + " " + players[i].getName() + " " + players[i].getPoints();
            }
            else {
                status += "no team " + players[i].getNumber() + " " + players[i].getName() + " " + players[i].getPoints();
            }
            if(i + 1 != 2) {
                status += "\n";
            }
        }
        return status;
    }

}
