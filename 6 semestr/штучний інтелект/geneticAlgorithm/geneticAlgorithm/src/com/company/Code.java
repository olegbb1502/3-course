package com.company;

import java.util.ArrayList;

/**
 * Created by Наталья on 3/10/2016.
 */
public class Code {
    public ArrayList<City> list;
    public int distance;

    public Code(ArrayList<City> list) {
        this.list = new ArrayList<>(list);
    }

    public Code(Code code) {
        this.list = new ArrayList<>(code.list);
    }

    public void set(int i,City city) {
        this.list.set(i,city);
    }

    public City remove(int i) {
        return this.list.remove(i);
    }

    public boolean remove(City city) {
        return this.list.remove(city);
    }

    public int countDistance() {
        distance = 0;
        for(int i=0; i<list.size()-1; i++) {
            distance += Math.sqrt(Math.pow(list.get(i).x-list.get(i+1).x,2)+Math.pow(list.get(i).y-list.get(i+1).y,2));
        }
        distance += Math.sqrt(Math.pow(list.get(list.size()-1).x-list.get(0).x,2)+
                Math.pow(list.get(list.size()-1).y-list.get(0+1).y,2));
        return distance;
    }

    public int size() {
        return list.size();
    }

    public City get(int i) {
        return list.get(i);
    }

}
