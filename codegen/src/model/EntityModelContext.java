package model;

import java.util.Set;

public class EntityModelContext {

    private Set<EntityModel> _entityModels ;

    public EntityModelContext(Set<EntityModel> _entityModels) {
        this._entityModels = _entityModels;
    }

    public Set<EntityModel> getEntityModels() {
        return _entityModels;
    }
}
