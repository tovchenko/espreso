package com.soomla.cocos2dx.common;

import android.opengl.GLSurfaceView;
import com.soomla.rewards.BadgeReward;
import com.soomla.rewards.RandomReward;
import com.soomla.rewards.SequenceReward;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 7/1/14
 *         time 10:17 AM
 */
public class CoreService extends AbstractSoomlaService {

    private static CoreService INSTANCE = null;

    private boolean inited = false;

    public static CoreService getInstance() {
        if (INSTANCE == null) {
            synchronized (CoreService.class) {
                if (INSTANCE == null) {
                    INSTANCE = new CoreService();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private CoreEventHandlerBridge coreEventHandlerBridge;

    public CoreService() {
        coreEventHandlerBridge = new CoreEventHandlerBridge();

        final DomainFactory domainFactory = DomainFactory.getInstance();

        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_BADGE, new DomainFactory.Creator<BadgeReward>() {
            @Override
            public BadgeReward create(JSONObject jsonObject) {
                try {
                    return new BadgeReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_RANDOM, new DomainFactory.Creator<RandomReward>() {
            @Override
            public RandomReward create(JSONObject jsonObject) {
                try {
                    return new RandomReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_SEQUENCE, new DomainFactory.Creator<SequenceReward>() {
            @Override
            public SequenceReward create(JSONObject jsonObject) {
                try {
                    return new SequenceReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });

        final NdkGlue ndkGlue = NdkGlue.getInstance();

        ndkGlue.registerCallHandler("CCCoreService::init", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                CoreService.getInstance().init();
            }
        });
    }

    private void init() {
        final GLSurfaceView glSurfaceView = glSurfaceViewRef.get();
        if (glSurfaceView != null) {
            coreEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }

        inited = true;
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        if (inited) {
            coreEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        } else {
            glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
        }
    }
}
