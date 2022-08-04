package org.g.pc.strings.doublets;

import java.io.IOException;
import java.util.*;

class Main {
    static String ReadLn(int maxLg)  // utility function to read from stdin
    {
        byte lin[] = new byte[maxLg];
        int lg = 0, car = -1;
        String line = "";

        try {
            while (lg < maxLg) {
                car = System.in.read();
                if ((car < 0) || (car == '\n')) break;
                lin[lg++] += car;
            }
        } catch (IOException e) {
            return (null);
        }

        if ((car < 0) && (lg == 0)) return (null);  // eof
        return (new String(lin, 0, lg));
    }

    public static void main(String args[])  // entry point from OS
    {
        Main myWork = new Main();  // create a dinamic instance
        myWork.Begin();            // the true entry point
    }

    boolean isDoublet(String s1, String s2) {
        int l = s1.length();
        if (l != s2.length()) {
            return false;
        }

        int d = 0;
        for (int i = 0; i < l; i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                d++;
                if (d > 1) {
                    break;
                }
            }
        }

        return d == 1;
    }

    Map<String, String> findPath(Map<String, HashSet<String>> graph, String start, String end) {
        Map<String, String> parentMap = new HashMap<>(graph.size());
        Set<String> discoveredSet = new HashSet<>(graph.size());
        Queue<String> queue = new LinkedList<>();

        queue.offer(start);
        discoveredSet.add(start);


        for (String v = queue.poll(); v != null; v = queue.poll()) {
            Set<String> adjacency = graph.get(v);
            if (adjacency != null && !adjacency.isEmpty()) {
                for (String s : adjacency) {
                    if (s.equals(end)) {
                        parentMap.put(s, v);
                        return parentMap;
                    }

                    if (!discoveredSet.contains(s)) {
                        queue.offer(s);
                        discoveredSet.add(s);
                        parentMap.put(s, v);
                    }
                }
            }
        }

        return parentMap;
    }

    void Begin() {
        HashMap<Integer, HashMap<String, HashSet<String>>> dict = new HashMap<>();

        String line;
        while ((line = Main.ReadLn(255)) != null) {
            if (line.length() == 0) {
                break;
            }

            HashMap<String, HashSet<String>> subDict = dict.get(line.length());
            if (subDict == null) {
                subDict = new HashMap<>();
                subDict.put(line, new HashSet<>());
                dict.put(line.length(), subDict);
            } else {
                subDict.put(line, new HashSet<>());
            }

            if (subDict.keySet().size() > 1) {
                for (String key : subDict.keySet()) {
                    if (!key.equals(line)) {
                        if (isDoublet(key, line)) {
                            subDict.get(key).add(line);
                            subDict.get(line).add(key);
                        }
                    }
                }
            }
        }

        int cases = 0;
        while ((line = Main.ReadLn(255)) != null) {
            if (cases > 0) {
                System.out.println();
            }

            cases++;

            final String[] words = line.split("\\s");
            int l = words[0].length();
            if (l != words[1].length()) {
                System.out.println("No solution.");
                continue;
            }

            final HashMap<String, HashSet<String>> graph = dict.get(l);
            if (graph == null || !graph.containsKey(words[0]) || !graph.containsKey(words[1])) {
                System.out.println("No solution.");
                continue;
            }

            final Map<String, String> path = findPath(graph, words[0], words[1]);
            if (!path.containsKey(words[1])) {
                System.out.println("No solution.");
                continue;
            }

            Stack<String> stack = new Stack<>();

            for (String word = words[1]; word != null; word = path.get(word)) {
                stack.push(word);
            }

            while (!stack.empty()) {
                String word = stack.pop();
                System.out.println(word);
            }
        }
    }
}
