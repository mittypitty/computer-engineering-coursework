import java.util.*;

public class Task {
    private static User supervisor;
    private User[] employees;
    int i = 0;
    private User employer;
    private String title;
    private boolean isCompleted;
    public Task(String title, User employer, User employee) {
        this.isCompleted = false;
        this.employees = new User[0];
        //using addEmployee to add it
        addEmployee(employee);
        //check if supervisor is null or not, and if it is it will equals to employer !!
        if(supervisor == null) {
            supervisor = employer;
        }
        this.employer = employer;
        this.title = title;
    }

    public void addEmployee(User emp) {
        //making a new array that doesnt have an special lenght
        User[] helpEmployees = new User[i + 1];

        for (int index = 0; index < i; index++) {
          helpEmployees[index] = this.employees[index];
        }
        int j = i + 1;
        helpEmployees[j - 1] = emp;
        // Update the employee list
        this.employees = helpEmployees;
        i++;
      }
      
    public void complete() {
        if(i >= 3) {
            isCompleted = true;
        }
    }
    public User getSupervisor() {
        return supervisor;
    }
    // public void setSupervisor(User supervisor) {
    //     this.supervisor = supervisor;
    // } 

    public User[] getEmployees() {
        return employees;
    }
    // public void setEmployees (User[] employees) {
    //     this.employees = employees;
    // }

    public User getEmployer() {
        return employer;
    }
    // public void setEmployer(User employer) {
    //     this.employer = employer;
    // }

    public String getTitle() {
        return title;
    }
    // public void setTitle(String title) {
    //     this.title = title;
    // }
    
    public boolean isCompleted() {
        return isCompleted;
    }
    // public void setIsCompleted(boolean isCompleted) {
    //     this.isCompleted = isCompleted;
    // }
    
    

}
