class Wheel {
    private String tireCompany;
    private String tireSize;
    public Wheel(String tireCompany, String tireSize) {
        this.tireCompany = tireCompany;
        this.tireSize = tireSize;
    }
    public String getTireCompany() {
        return tireCompany;
    }
    public String getTireSize () {
        return tireSize;
    }
    public void setTireCompany(String tireCompany) {
        this.tireCompany = tireCompany;
    }
    public void setTireSize(String tireSize) {
        this.tireSize = tireSize;
    }
}
