import java.util.ArrayList;
public abstract class Inventory {
    String manager_name;
    int capacity;

    abstract boolean AddToInventory(Item item);

    public abstract String getManager_name();

    abstract int getItemCount();

    public abstract String getMobile(String id);

    public abstract String getTV(String id);

    public abstract boolean RemoveFromInventory(Item item);

    public abstract String getTank(String id);

    public abstract String getGun(String id);


}

class HouseHold extends Inventory {

    private int itemCount;
    private ArrayList<Item> TV = new ArrayList<Item>();
    private ArrayList<Item> Mobile = new ArrayList<Item>();

    HouseHold(int capacity,String manager_name){
        this.capacity = capacity;
        this.manager_name = manager_name;

    }
    @Override
    public String getManager_name() {
        return manager_name;
    }

    @Override
    int getItemCount() {
        return TV.size() + Mobile.size();
    }


    @Override
    boolean AddToInventory(Item item) {
        if(capacity == Mobile.size() + TV.size()) {
            return false;
        }
        if(item.getPrice() < 1000000) {
            return false;
        }
        if(item.getPrice() > 20000000 && item.getPrice() < 25000000) {
            return false;
        }
        if(item.getPrice() > 50000000) {
            return false;
        }
        int n = 0;
        int m = 0;
        boolean status = true;
        for (int i = 0; i < item.getId().length(); i++) {
            if (item.getId().charAt(i) == 'a') {
                n++;
            }
            if (item.getId().charAt(i) == 'b') {
                m++;
            }
            if (item.getId().charAt(i) != 'a' && item.getId().charAt(i) != 'b') {
                status = false;
                break;
            }
            if (item.getId().charAt(i) == 'b') {
                if (i + 1 < item.getId().length()) {
                    if (item.getId().charAt(i + 1) == 'a') {
                        status = false;
                        break;
                    }
                }
            }
        }
        if((n + m) % 2 == 0) {
            status = false;
        }
        if(status) {
            if(item.getType() == Item_Type.Mobile) {
                Mobile.add(item);
            }
            if(item.getType() == Item_Type.TV) {
                TV.add(item);
            }
        }
        return status;
    }




    @Override
    public String getMobile(String id) {
        String str = "";
        int mobileIndex = 0;
        boolean hasMobile = false;
        for(int i = 0 ; i < Mobile.size() ; i++) {
            if(Mobile.get(i).getId().equals(id)) {
                mobileIndex = i + 1;
                hasMobile = true;
            }
        }
        if((hasMobile && Mobile.get(mobileIndex - 1).getType() == Item_Type.Mobile)) {
            str = "number of Mobile with this id " + id + " is: " + mobileIndex;
        }
        else {
            str = "there is no Mobile with this id: " + id;
        }
        return str;
    }

    @Override
    public String getTV(String id) {
        String str = "";
        int tvIndex = 0;
        boolean hasTv = false;
        for(int i = 0 ; i < TV.size() ; i++) {
            if(TV.get(i).getId().equals(id)) {
                tvIndex = i + 1;
                hasTv = true;
            }
        }
        if((hasTv && TV.get(tvIndex - 1).getType() == Item_Type.TV )) {
            str = "number of TV with this id " + id + " is: " + tvIndex;
        }
        else {
            str = "there is no TV with this id: " + id;
        }
        return str;
    }

    @Override
    public boolean RemoveFromInventory(Item item) {
        boolean status = false;
        if(TV.contains(item)) {
            TV.remove(item);
            status = true;
        }
        if(Mobile.contains(item)) {
            Mobile.remove(item);
            status = true;
        }
        return status;
    }

    @Override
    public String getTank(String id) {
        return null;
    }

    @Override
    public String getGun(String id) {
        return null;
    }


}

class MilitaryHold extends Inventory {

    private int itemCount;
    private ArrayList<Item> Gun = new ArrayList<Item>();
    private ArrayList<Item> Tank = new ArrayList<Item>();


    MilitaryHold(int capacity, String manager_name){
        this.capacity = capacity;
        this.manager_name = manager_name;
    }


    @Override
    boolean AddToInventory(Item item) {
        if(capacity == Gun.size() + Tank.size() ) {
            return false;
        }
        if(item.getPrice() < 60000000) {
            return false;
        }
        if(item.getPrice() > 90000000 && item.getPrice() < 100000000) {
            return false;
        }
        if(item.getPrice() > 300000000) {
            return false;
        }
        int x = 0;
        boolean status = true;

        for (int i = 0; i < item.getId().length(); i++) {
            if(i + 1 < item.getId().length()) {
                if (item.getId().charAt(i) == 'b' && item.getId().charAt(i + 1) == 'a') {
                    x++;
                }
            }
        }
        if(x % 2 == 0) {
            status = false;
        }
        if(status) {
            if(item.getType() == Item_Type.Gun) {
                Gun.add(item);
            }
            if(item.getType() == Item_Type.Tank) {
                Tank.add(item);
            }
        }
        return status;
    }

    @Override
    int getItemCount() {
        return Gun.size() + Tank.size();
    }

    @Override
    public String getMobile(String id) {
        return "";
    }

    @Override
    public String getTV(String id) {
        return "";
    }

    @Override
    public boolean RemoveFromInventory(Item item) {
        boolean status = false;
        if(Gun.contains(item)) {
            Gun.remove(item);
            status = true;
        }
        if(Tank.contains(item)) {
            Tank.remove(item);
            status = true;
        }
        return status;
    }

    @Override
    public String getManager_name() {
        return manager_name;
    }

    @Override
    public String getTank(String id) {
        String str = "";
        int tankIndex = 0;
        boolean hasTank = false;
        for(int i = 0 ; i < Tank.size() ; i++) {
            if(Tank.get(i).getId().equals(id)) {
                tankIndex = i + 1;
                hasTank = true;
            }
        }
        if((hasTank && Tank.get(tankIndex - 1).getType() == Item_Type.Tank )) {
            str = "number of Tank with this id " + id + " is: " + tankIndex;
        }
        else {
            str = "there is no Tank with this id: " + id;
        }
        return str;
    }

    @Override
    public String getGun(String id) {
        String str = "";
        int gunIndex = 0;
        boolean hasGun = false;
        for(int i = 0 ; i < Gun.size() ; i++) {
            if(Gun.get(i).getId().equals(id)) {
                gunIndex = i + 1;
                hasGun = true;
            }
        }
        if((hasGun && Gun.get(gunIndex - 1).getType() == Item_Type.Gun)) {
            str = "number of Gun with this id " + id + " is: " + gunIndex;
        }
        else {
            str = "there is no Gun with this id: " + id;
        }
        return str;
    }


}

class Item{
    private String name;
    private String id;
    private long price;
    private Item_Type type;

    Item(String name,String id,long price){
        if(price >= 1000000 && price <= 20000000) {
            this.name = name;
            this.id = id;
            this.price = price;
        }
        if(price >= 25000000 && price <= 50000000) {
            this.name = name;
            this.id = id;
            this.price = price;
        }
        if(price >= 60000000 && price <= 90000000) {
            this.name = name;
            this.id = id;
            this.price = price;
        }
        if(price >= 100000000 && price <= 300000000) {
            this.name = name;
            this.id = id;
            this.price = price;
        }
    }

    public String getName() {
        return name;
    }

    public long getPrice() {
        return price;
    }

    public String getId() {
        return id;
    }

    public Item_Type getType() {
        if(price >= 1000000 && price <= 20000000) {
            return Item_Type.Mobile;
        }
        if(price >= 25000000 && price <= 50000000) {
            return Item_Type.TV;
        }
        if(price >= 60000000 && price <= 90000000) {
            return Item_Type.Gun;
        }
        if(price >= 100000000 && price <= 300000000) {
            return Item_Type.Tank;
        }
        return null;
    }
}

enum Item_Type {
    Mobile,Tank,TV,Gun
}


