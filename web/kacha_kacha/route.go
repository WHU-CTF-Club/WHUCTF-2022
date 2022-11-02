package main

import (
	"github.com/gin-gonic/gin"
	"github.com/maybemia/kacha_kacha/controller"
	"github.com/maybemia/kacha_kacha/middleware"
)

func CollectRoutes(r *gin.Engine) *gin.Engine {

	r.Use(GinContextToContextMiddleware())
	//注册
	r.POST("/register", controller.Register)
	//登录
	r.POST("/login", controller.Login)
	//返回用户信息
	r.GET("/info", middleware.AuthMiddleware(), controller.Info)

	return r

}
