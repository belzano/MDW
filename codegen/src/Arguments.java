import com.google.common.base.Strings;
import com.google.common.collect.ImmutableSet;
import generation.TargetOutput;

import java.util.Set;

public class Arguments {

    private Arguments() {}

    private String _buildDir = "/home/guillaume.evrard/dev/MDW/codegen/tmp/build";
    private String _outputDir = "/home/guillaume.evrard/dev/MDW/codegen/tmp/out";
    private String _entityModelsRootDir ="/home/guillaume.evrard/dev/MDW/codegen/testmodel";
    private Set<TargetOutput> _targetOutput = ImmutableSet.copyOf(TargetOutput.values());

    public String getTmpBuildDir() {
        return _buildDir;
    }

    public String getOutputDir() {
        return _outputDir;
    }

    public String getEntityModelsRootDir() {
        return _entityModelsRootDir;
    }

    public Set<TargetOutput> getTargetOutputs() {
        return _targetOutput;
    }

    public boolean isValid(){
        return (!Strings.isNullOrEmpty(_buildDir)) && (!Strings.isNullOrEmpty(_entityModelsRootDir));
    }

    public static Arguments parse(String[] varargs){
        Arguments args = new Arguments();
        for (String token : varargs) {
            if (token.startsWith("--build-dir=")) {
                args._buildDir = token.split("=")[1];
            }
            else if (token.startsWith("--models-dir=")) {
                args._entityModelsRootDir = token.split("=")[1];
            }
            else {
                throw new IllegalArgumentException("Unhandled option " + token);
            }
        }

        if (! args.isValid()) {
            throw new IllegalArgumentException();
        }

        return args;
    }

}
