package com.company;

import java.lang.reflect.Array;
import java.util.*;

/**
 * Created by Наталья on 3/10/2016.
 */
public class GeneticAlgorithm {
    private ArrayList<Code> codeSpace;
    private int crossoverNumber = 3;
    private int mutationNumber = 2;
    private int ITERATION_NUM = 10_000;
    private int bufferSize = 2;//amount of pretenders to commit crossover on each stage(tournament)
    private ArrayList<Code> history;
    private Code result;

    public GeneticAlgorithm(ArrayList<Code> codeSpace) {
        this.codeSpace = new ArrayList<>(codeSpace);
        history = new ArrayList<>();
    }

    public ArrayList<Code> Solve() {
        int iteration = 0;
        while((iteration<ITERATION_NUM)) {
            commitCrossover();
            commitMutation();
            reducePopulation();
            if(iteration%10 == 0) {
                history.add(result);
                //System.out.println(iteration);
            }
            iteration++;
        }
        return history;
    }

    private void commitMutation() {
        Random random = new Random();
        ArrayList<Code> code = new ArrayList<>(codeSpace);
        int position = 0;
        for(int i=0; i<mutationNumber; i++) {
            position = random.nextInt(code.size());
            codeSpace.set(position, alterCode(code.remove(position)));
        }
    }

    private Code alterCode(Code code) {
        Random random = new Random();
        int n1 = random.nextInt(code.size());
        City city1 = new City(code.get(n1));
        int n2 = random.nextInt(code.size());
        City city2 = new City(code.get(n2));
        code.set(n1,city2);
        code.set(n2,city1);
        return code;
    }

    private ArrayList<Code> chooseParentsForCrossover() {
        ArrayList<Code> parents = new ArrayList<>();
        for(int i=0; i<crossoverNumber*2; i++) {
            ArrayList<Code> buffer = new ArrayList<>(codeSpace);
            ArrayList<Code> pretenders = new ArrayList<>();
            Random random = new Random();
            for(int j=0; j<bufferSize; j++) {
                pretenders.add(buffer.remove(random.nextInt(buffer.size())));
            }
            Collections.sort(pretenders, new Comparator<Code>() {
                public int compare(Code o1, Code o2) {
                    if (o1.distance >= o2.distance) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            });
            parents.add(pretenders.get(0));
        }
        return parents;
    }

    public void commitCrossover() {
        ArrayList<Code> parents = chooseParentsForCrossover();
        for(int i=0; i<crossoverNumber; i++) {
            newMultipleCrossover(parents);
        }
    }

    public void newCrossover(ArrayList<Code> parents) {
        /*for(int i=0; i<firstParent.size(); i++) {
            System.out.print(firstParent.get(i).order+"-");
        }
        System.out.println();*/
        ArrayList<Code> buffer = new ArrayList<>(parents);
        Random random = new Random();
        Code firstParent = buffer.remove(random.nextInt(buffer.size()));
        Code secondParent = buffer.remove(random.nextInt(buffer.size()));
        while(firstParent.equals(secondParent) && buffer.size()!=0) {
            secondParent = buffer.remove(random.nextInt(buffer.size()));
        }
        Code firstChild = new Code(firstParent);
        Code secondChild = new Code(secondParent);
        Code firstParentBuf = new Code(firstParent);
        Code secondParentBuf = new Code(secondParent);
        int edge = random.nextInt(firstParent.size()-1)+1;
        for(int i=0; i<edge; i++) {
            firstParentBuf.remove(0);
            secondParentBuf.remove(0);
        }
        for(int i=edge; i<firstChild.size(); i++) {
            if(!checkIfUnique(secondParent.get(i), firstChild, i)) {
                firstChild.set(i,firstParentBuf.remove(0));
            } else {
                firstChild.set(i,secondParent.get(i));
                firstParentBuf.remove(secondParent.get(i));
            }
            if(!checkIfUnique(firstParent.get(i), secondChild, i)) {
                secondChild.set(i,secondParentBuf.remove(0));
            } else {
                secondChild.set(i,firstParent.get(i));
                secondParentBuf.remove(firstParent.get(i));
            }
        }
        codeSpace.add(firstChild);
        codeSpace.add(secondChild);
    }

    public void newMultipleCrossover(ArrayList<Code> parents) {
        ArrayList<Code> buffer = new ArrayList<>(parents);
        Random random = new Random();
        Code firstParent = buffer.remove(random.nextInt(buffer.size()));
        Code secondParent = buffer.remove(random.nextInt(buffer.size()));
        while(firstParent.equals(secondParent) && buffer.size()!=0) {
            secondParent = buffer.remove(random.nextInt(buffer.size()));
        }
        Code firstChild = new Code(firstParent);
        Code secondChild = new Code(secondParent);
        Code firstParentBuf = new Code(new ArrayList<>());
        Code secondParentBuf = new Code(new ArrayList<>());
        int edge1 = random.nextInt(firstParent.size()-2-1)+1;
        int edge2 = random.nextInt(firstParent.size()-edge1-2)+edge1+2;
        for(int i=edge2; i<firstParent.size(); i++) {
            firstParentBuf.list.add(firstChild.get(i));
            secondParentBuf.list.add(secondChild.get(i));
        }
        for(int i=0; i<edge2; i++) {
            firstParentBuf.list.add(firstChild.get(i));
            secondParentBuf.list.add(secondChild.get(i));
        }
        for(int i=edge1; i<edge2; i++) {
            secondParentBuf.remove(firstChild.get(i));
            firstParentBuf.remove(secondChild.get(i));
        }
        int count = 0;
        for(int i=edge2; i<firstParent.size(); i++) {
            firstChild.set(i,secondParentBuf.get(count));
            secondChild.set(i,firstParentBuf.get(count++));
        }
        for(int i=0; i<edge1; i++) {
            firstChild.set(i,secondParentBuf.get(count));
            secondChild.set(i,firstParentBuf.get(count++));
        }
        codeSpace.add(firstChild);
        codeSpace.add(secondChild);
    }

    public boolean checkIfUnique(City city, Code code, int size) {
        for(int i=0; i<size; i++) {
            if(city.equals(code.get(i))) {
                return false;
            }
        }
        return true;
    }

    public void reducePopulation() {
        //System.out.print("total: ");
        for (Code code : codeSpace) {
            code.countDistance();
        }
        //System.out.println();
        Collections.sort(codeSpace, new Comparator<Code>() {
            public int compare(Code o1, Code o2) {
                if (o1.distance >= o2.distance) {
                    return 1;
                } else {
                    return -1;
                }
            }
        });
        //System.out.print("deleted: ");
        while(codeSpace.size()!=Main.CodeNumber){
            //System.out.print(codeSpace.get(codeSpace.size()-1).distance+" ");
            codeSpace.remove(codeSpace.size()-1);
        }
        //System.out.println(codeSpace.size());
        result = codeSpace.get(0);
        //for(int i=0; i<result.size(); i++) {
        //    System.out.print(result.get(i).order+"-");
        //}
        //System.out.println();
        //System.out.println(result.distance);
    }
}