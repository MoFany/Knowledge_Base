package com.baomidou.mybatisplus.samples.reduce.springmvc.configurations;

import com.baomidou.mybatisplus.annotation.DbType;
import com.baomidou.mybatisplus.core.config.GlobalConfig;
import com.baomidou.mybatisplus.core.incrementer.IKeyGenerator;
import com.baomidou.mybatisplus.extension.plugins.MybatisPlusInterceptor;
import com.baomidou.mybatisplus.extension.plugins.inner.PaginationInnerInterceptor;
import org.mybatis.spring.annotation.AutoMapperScan;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Arrays;

/**
 * @author  alan2lin
 * @date 2019年07月04日
 */
@Configuration
@AutoMapperScan(basePackages = "com.baomidou.mybatisplus.samples.reduce.springmvc.mapper", beanPackages = "com.baomidou.mybatisplus.samples.reduce.springmvc.entity",superMapperClassName = "com.baomidou.mybatisplus.samples.reduce.springmvc.mapper.MyBaseMapper",excludedBeans = "com.baomidou.mybatisplus.samples.reduce.springmvc.entity.D*")
public class DbConfigurations {

    @Bean
    public MybatisPlusInterceptor mybatisPlusInterceptor() {
        MybatisPlusInterceptor mybatisPlusInterceptor = new MybatisPlusInterceptor();
        mybatisPlusInterceptor.addInnerInterceptor(new PaginationInnerInterceptor());
        return mybatisPlusInterceptor;
    }

    @Bean
    public GlobalConfig globalConfiguration() {
        GlobalConfig conf = new GlobalConfig();
        conf.setDbConfig(new GlobalConfig.DbConfig().setKeyGenerators(Arrays.asList(
                // h2 1.x 的写法（默认 2.x 的写法）
                new IKeyGenerator() {

                    @Override
                    public String executeSql(String incrementerName) {
                        return "select " + incrementerName + ".nextval";
                    }

                    @Override
                    public DbType dbType() {
                        return DbType.POSTGRE_SQL;
                    }
                }
        )));
        return conf;
    }
}
