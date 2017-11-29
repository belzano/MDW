package model;

import java.util.HashSet;
import java.util.Set;

public class EntityModelContext {

    private String _projectName;
    private Set<EntityTypeModel> _entityModels = new HashSet<>();

    public EntityModelContext(String projectName) {
        _projectName = projectName;
    }

    public Set<EntityTypeModel> getEntityModels() {
        return _entityModels;
    }

    public String getProjectName() {
        return _projectName;
    }
}
