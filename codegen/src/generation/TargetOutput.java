package generation;

public enum TargetOutput {
    CPP,
    HPP,
    CMAKE,
    JAVA;

    public static TargetOutput[] ALL = TargetOutput.values();
}
