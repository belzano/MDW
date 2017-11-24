package model;

import java.util.HashSet;
import java.util.Set;

public class EntityModelContext {

    private Set<EntityTypeModel> _entityModels = new HashSet<>();

    public EntityModelContext() {
    }

    public Set<EntityTypeModel> getEntityModels() {
        return _entityModels;
    }
}
