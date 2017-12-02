package reflection;


import com.google.common.collect.ImmutableSet;
import org.reflections.Reflections;
import org.reflections.scanners.MemberUsageScanner;
import org.reflections.scanners.SubTypesScanner;
import org.reflections.scanners.TypeAnnotationsScanner;
import org.reflections.util.ConfigurationBuilder;

import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.HashSet;
import java.util.Set;

public class Collector {

    private Reflections _introspector = null;

    public Collector(URL url){
        init(url);
    }

    private void init(URL url) {

        System.out.println("Initializing introspector on [" + url + "]");

        loadJars(url);

        TypeAnnotationsScanner typeAnnotationScanner = new TypeAnnotationsScanner();
        SubTypesScanner subTypesScanner = new SubTypesScanner(false);
        MemberUsageScanner memberUsageScanner = new MemberUsageScanner();

        ConfigurationBuilder configBuilder = new ConfigurationBuilder()
                .setScanners( typeAnnotationScanner,
                        subTypesScanner,
                        memberUsageScanner)
                .setUrls(ImmutableSet.of(url));
        _introspector = new Reflections(configBuilder);
    }

    private void loadJars(URL url) {
        URLClassLoader sysLoader = (URLClassLoader) ClassLoader.getSystemClassLoader();
        Class sysClass = URLClassLoader.class;
        try {
            Method method = sysClass.getDeclaredMethod("addURL", new Class[]{URL.class});
            method.setAccessible(true);
            System.out.println(" - loading " + url);
            method.invoke(sysLoader, new Object[]{ url });
        } catch(Exception ex) {
            System.err.println(ex.getMessage());
        }
    }

    public Set<Class<?>> collectCodeGenClasses() throws ClassNotFoundException {
        Set<Class<?>> classes = new HashSet<>();
        for (String type: _introspector.getAllTypes()) {
            classes.add(Class.forName(type));
        }
        System.out.println("Collected " + classes.size() + " codegen classes");
        return classes;
    }

}
