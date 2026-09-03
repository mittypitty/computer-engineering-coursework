import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Team {
    private String name;
    private int capacityOfTeam = 3;
    private int score = 0;
    private Player captain = null;
    private Player[] players;

    public Player[] getPlayers() {
        return players;
    }

    public Team(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }
    public String getName() {
        return name;
    }
    public void setScore(int score){
        this.score = score;
    }
    public int getScore() {
        return score;
    }
    public int getCapacityOfTeam() {
        return capacityOfTeam;
    }

    public String setContract(Player p){
        String status = "";
        if(p.getTeam().getName() == null && players.length < 3) {
            Player[] tempPlayers = new Player[players.length + 1];
            System.arraycopy(players, 0, tempPlayers, 0, players.length);
            tempPlayers[players.length] = p;
            this.players = tempPlayers;
            p.setTeam(this);
            
            status = "setting contract is successful";
        }
        else if(p.getTeam().getName() == name) {
            status = "this player is already on a team";
        }
        else if(p.getTeam().getName() != name && p.getTeam().getName() != null) {
            status = "this player is on a different team";
        }
        if(players.length >= 3) {
            status = "team capacity is full";
        }
        if(players.length >= 3 && p.getTeam().getName() == name) {
            status = "this player is already on a team";
        }
        setCaptain();
        return status;
    }

    public void setCaptain() {
        for (int i = 0; i < players.length; i++) {
            for (int j = i + 1; j < players.length; j++) {
                if (players[i].getPoints() < players[j].getPoints()) {
                    Player temp = players[i];
                    players[i] = players[j];
                    players[j] = temp;
                }
            }
        }
        captain = players[0];
    }

    public Player getCaptain() {
        return captain;
    }


    public String firePlayer(Player p){
        String status = "this player is not in " + name;
        for(int i = 0 ; i< players.length ; i++) {
            if(players[i] == p) {
                status =  "player has removed from "  + name;
                p.setTeam(null);
            }
        }
        setCaptain();
        p.setPoints(0); 
        return status;
    }

    public String listOfPlayers() {
        for (int i = 0; i < players.length; i++) {
            for (int j = i + 1; j < players.length; j++) {
                if (players[i].getPoints() < players[j].getPoints()) {
                    Player temp = players[i];
                    players[i] = players[j];
                    players[j] = temp;
                }
            }
        }
        String status = "";

        for(int i = 0 ; i < players.length ; i++) {
            if(players[i] != null){
                status = status + (i + 1) + "." + players[i].getNumber() + " " + players[i].getName() + ":" + players[i].getPoints();
                if(i + 1 != players.length) {
                    status += "\n";
                }
            }
        }
        return status;

    }
}
