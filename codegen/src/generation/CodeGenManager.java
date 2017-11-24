package generation;

import generation.driver.ContextGenDriver;
import generation.driver.cpp.ContextGenDriverCppDecl;
import generation.driver.cpp.ContextGenDriverCppDef;
import generation.driver.java.ContextGenDriverJava;
import model.EntityModelContext;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Set;

public class CodeGenManager {

    private String _outDirectory;

    public CodeGenManager(String outDirectory) throws Exception {
        _outDirectory = outDirectory;
        Files.createDirectories(Paths.get(new File(_outDirectory).toURI()));
    }

    public void generate(Set<TargetOutput> targets, EntityModelContext context) {
        Set<ContextGenDriver> generators = getGenerators(targets);
        for (ContextGenDriver generator: generators) {
            generator.generate(context);
        }
    }

    private Set<ContextGenDriver> getGenerators(Set<TargetOutput> target) {
        Set<ContextGenDriver> generators = new HashSet<>();
        if (target.contains(TargetOutput.CPP)) {
            generators.add(new ContextGenDriverCppDef(_outDirectory + "/cpp/src"));
        }
        if (target.contains(TargetOutput.HPP)) {
            generators.add(new ContextGenDriverCppDecl(_outDirectory + "/cpp/include"));
        }
        if (target.contains(TargetOutput.JAVA)) {
            generators.add(new ContextGenDriverJava(_outDirectory + "/java"));
        }
        return generators;
    }

}
